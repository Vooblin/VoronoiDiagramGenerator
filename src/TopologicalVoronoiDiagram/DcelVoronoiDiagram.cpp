#include <vdg/Point.h>
#include <vdg/TopologicalVoronoiDiagram/DcelVoronoiDiagram.h>

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace vdg {

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addVertex(
    const Point2D& point) {
    vertices_.push_back({point, std::nullopt});
    return (vertices_.size() - 1) << 2;
}

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addEdge(ElementId start,
                                                          ElementId end) {
    const auto start_idx = start >> 2;
    const auto end_idx = end >> 2;
    half_edges_.push_back({start_idx, half_edges_.size() + 1, edges_.size(),
                           std::nullopt, std::nullopt, std::nullopt});
    half_edges_.push_back({end_idx, half_edges_.size() - 1, edges_.size(),
                           std::nullopt, std::nullopt, std::nullopt});
    vertices_[start_idx].incident_edge_idx = half_edges_.size() - 2;
    vertices_[end_idx].incident_edge_idx = half_edges_.size() - 1;
    edges_.push_back({half_edges_.size() - 2, half_edges_.size() - 1});
    return ((edges_.size() - 1) << 2) + 1;
}

DcelVoronoiDiagram::ElementId DcelVoronoiDiagram::addCell(
    const std::vector<ElementId>& edges) {
    const auto first_idx = edges.front() >> 2;
    const auto first_edge = edges_.at(first_idx);
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
                const auto edge_idx = edge >> 2;
                const auto edge_data = edges_.at(edge_idx);
                return ((half_edges_[edge_data.half_edge_1_idx].origin_idx ==
                         next_origin_idx) &&
                        (edge_data.half_edge_1_idx !=
                         half_edges_[current_half_edge_idx].twin_idx)) ||
                       ((half_edges_[edge_data.half_edge_2_idx].origin_idx ==
                         next_origin_idx) &&
                        (edge_data.half_edge_2_idx !=
                         half_edges_[current_half_edge_idx].twin_idx));
            });
        const auto next_idx = next_edge >> 2;
        const auto next_half_edge_idx =
            (half_edges_[edges_[next_idx].half_edge_1_idx].origin_idx ==
             next_origin_idx)
                ? edges_[next_idx].half_edge_1_idx
                : edges_[next_idx].half_edge_2_idx;

        half_edges_[current_half_edge_idx].next_idx = next_half_edge_idx;
        half_edges_[next_half_edge_idx].prev_idx = current_half_edge_idx;
        half_edges_[next_half_edge_idx].incident_face_idx = faces_.size() - 1;
        current_origin_idx = next_origin_idx;
        next_origin_idx =
            half_edges_[half_edges_[next_half_edge_idx].twin_idx].origin_idx;
        current_half_edge_idx = next_half_edge_idx;
    }
    return ((faces_.size() - 1) << 2) + 2;
}

const Point2D& DcelVoronoiDiagram::vertexPoint(ElementId vertex) const {
    return vertices_[vertex >> 2].crd;
}

std::pair<DcelVoronoiDiagram::ElementId, DcelVoronoiDiagram::ElementId>
    DcelVoronoiDiagram::edgeVertices(ElementId edge) const {
    const auto edge_data = edges_.at(edge >> 2);
    return {half_edges_[edge_data.half_edge_1_idx].origin_idx << 2,
            half_edges_[edge_data.half_edge_2_idx].origin_idx << 2};
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::cellFaces(
    ElementId cell, std::size_t dim) const {
    const auto face_data = faces_.at(cell >> 2);
    std::vector<ElementId> face_ids;
    auto current_half_edge_idx = face_data.incident_edge_idx;
    auto previous_half_edge_idx = face_data.incident_edge_idx;
    while (previous_half_edge_idx !=
           half_edges_[face_data.incident_edge_idx].prev_idx) {
        face_ids.push_back(
            (((dim == 1) ? half_edges_[current_half_edge_idx].edge_idx
                         : half_edges_[current_half_edge_idx].origin_idx)
             << 2) +
            dim);
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
        vertex_ids.push_back(idx << 2);
    }
    return vertex_ids;
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::edges() const {
    std::vector<ElementId> edge_ids;
    for (std::size_t idx = 0; idx < edges_.size(); ++idx) {
        edge_ids.push_back((idx << 2) + 1);
    }
    return edge_ids;
}

std::vector<DcelVoronoiDiagram::ElementId> DcelVoronoiDiagram::cells(
    [[maybe_unused]] std::size_t dim) const {
    std::vector<ElementId> cell_ids;
    for (std::size_t idx = 0; idx < faces_.size(); ++idx) {
        cell_ids.push_back((idx << 2) + 2);
    }
    return cell_ids;
}

}  // namespace vdg
