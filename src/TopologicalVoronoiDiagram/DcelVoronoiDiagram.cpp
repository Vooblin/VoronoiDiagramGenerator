#include <vdg/Point.h>
#include <vdg/TopologicalVoronoiDiagram/DcelVoronoiDiagram.h>

#include <algorithm>
#include <bit>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace vdg {

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addVertex(
    const Point2D& point) {
    vertices_.push_back({point, std::nullopt});
    return std::bit_cast<ElementId>(
        ElementIdRepresentation{0, vertices_.size() - 1});
}

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addEdge(ElementId start,
                                                          ElementId end) {
    const auto start_repr = std::bit_cast<ElementIdRepresentation>(start);
    const auto end_repr = std::bit_cast<ElementIdRepresentation>(end);
    half_edges_.push_back({start_repr.idx, half_edges_.size() + 1, std::nullopt,
                           std::nullopt, std::nullopt});
    half_edges_.push_back({end_repr.idx, half_edges_.size() - 1, std::nullopt,
                           std::nullopt, std::nullopt});
    vertices_[start_repr.idx].incident_edge_idx = half_edges_.size() - 2;
    vertices_[end_repr.idx].incident_edge_idx = half_edges_.size() - 1;
    edges_.push_back({half_edges_.size() - 2, half_edges_.size() - 1});
    return std::bit_cast<ElementId>(
        ElementIdRepresentation{1, edges_.size() - 1});
}

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addCell(
    const std::vector<ElementId>& edges) {
    const auto first_repr =
        std::bit_cast<ElementIdRepresentation>(edges.front());
    const auto first_edge = edges_.at(first_repr.idx);
    const auto first_half_edge_idx =
        half_edges_[first_edge.half_edge_1_idx].incident_face_idx.has_value()
            ? first_edge.half_edge_2_idx
            : first_edge.half_edge_1_idx;
    faces_.push_back({first_half_edge_idx});
    const auto origin_idx = half_edges_[first_half_edge_idx].origin_idx;
    auto next_origin_idx =
        half_edges_[half_edges_[first_half_edge_idx].twin_idx].origin_idx;
    auto current_origin_idx = next_origin_idx;
    auto current_half_edge_idx = first_half_edge_idx;
    while (current_origin_idx != origin_idx) {
        const auto next_edge = *std::find_if(
            edges.begin(), edges.end(),
            [current_half_edge_idx, next_origin_idx, this](ElementId edge) {
                const auto edge_repr =
                    std::bit_cast<ElementIdRepresentation>(edge);
                const auto edge_data = edges_.at(edge_repr.idx);
                return ((half_edges_[edge_data.half_edge_1_idx].origin_idx ==
                         next_origin_idx) &&
                        (edge_data.half_edge_1_idx !=
                         half_edges_[current_half_edge_idx].twin_idx)) ||
                       ((half_edges_[edge_data.half_edge_2_idx].origin_idx ==
                         next_origin_idx) &&
                        (edge_data.half_edge_2_idx !=
                         half_edges_[current_half_edge_idx].twin_idx));
            });
        const auto next_repr =
            std::bit_cast<ElementIdRepresentation>(next_edge);
        const auto next_half_edge_idx =
            (half_edges_[edges_[next_repr.idx].half_edge_1_idx].origin_idx ==
             next_origin_idx)
                ? edges_[next_repr.idx].half_edge_1_idx
                : edges_[next_repr.idx].half_edge_2_idx;
        half_edges_[current_half_edge_idx].next_idx = next_half_edge_idx;
        half_edges_[next_half_edge_idx].prev_idx = current_half_edge_idx;
        half_edges_[next_half_edge_idx].incident_face_idx = faces_.size() - 1;
        current_origin_idx = next_origin_idx;
        next_origin_idx =
            half_edges_[half_edges_[next_half_edge_idx].twin_idx].origin_idx;
        current_half_edge_idx = next_half_edge_idx;
    }
    return std::bit_cast<ElementId>(
        ElementIdRepresentation{2, faces_.size() - 1});
}

const Point2D& DcelVoronoiDiagram::vertexPoint(ElementId vertex) const {
    const auto repr = std::bit_cast<ElementIdRepresentation>(vertex);
    return vertices_[repr.idx].crd;
}

std::pair<DcelVoronoiDiagram::ElementId, DcelVoronoiDiagram::ElementId>
    DcelVoronoiDiagram::edgeVertices(ElementId edge) const {
    const auto repr = std::bit_cast<ElementIdRepresentation>(edge);
    const auto edge_data = edges_.at(repr.idx);
    return {std::bit_cast<ElementId>(ElementIdRepresentation{
                0, half_edges_[edge_data.half_edge_1_idx].origin_idx}),
            std::bit_cast<ElementId>(ElementIdRepresentation{
                0, half_edges_[edge_data.half_edge_2_idx].origin_idx})};
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::cellFaces(
    ElementId cell, std::size_t dim) const {
    const auto repr = std::bit_cast<ElementIdRepresentation>(cell);
    const auto face_data = faces_.at(repr.idx);
    std::vector<ElementId> face_ids;
    auto current_half_edge_idx = face_data.incident_edge_idx;
    auto previous_half_edge_idx = face_data.incident_edge_idx;
    while (previous_half_edge_idx !=
           half_edges_[current_half_edge_idx].prev_idx) {
        face_ids.push_back(std::bit_cast<ElementId>(ElementIdRepresentation{
            dim, (dim == 1) ? current_half_edge_idx
                            : half_edges_[current_half_edge_idx].origin_idx}));
        previous_half_edge_idx = current_half_edge_idx;
        current_half_edge_idx =
            half_edges_[current_half_edge_idx].next_idx.value_or(
                face_data.incident_edge_idx);
    }
    return face_ids;
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::vertices()
    const {
    std::vector<ElementId> vertex_ids;
    for (std::size_t idx = 0; idx < vertices_.size(); ++idx) {
        vertex_ids.push_back(
            std::bit_cast<ElementId>(ElementIdRepresentation{0, idx}));
    }
    return vertex_ids;
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::edges() const {
    std::vector<ElementId> edge_ids;
    for (std::size_t idx = 0; idx < edges_.size(); ++idx) {
        edge_ids.push_back(
            std::bit_cast<ElementId>(ElementIdRepresentation{1, idx}));
    }
    return edge_ids;
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::cells(
    [[maybe_unused]] std::size_t dim) const {
    std::vector<ElementId> cell_ids;
    for (std::size_t idx = 0; idx < faces_.size(); ++idx) {
        cell_ids.push_back(
            std::bit_cast<ElementId>(ElementIdRepresentation{2, idx}));
    }
    return cell_ids;
}

}  // namespace vdg
