#ifndef VDG_TOPOLOGICALVORONOIDIAGRAM_DCELVORONOIDIAGRAM_H
#define VDG_TOPOLOGICALVORONOIDIAGRAM_DCELVORONOIDIAGRAM_H

#include <vdg/Point.h>

#include <cstddef>
#include <optional>
#include <vector>

namespace vdg {

class DcelVoronoiDiagram {
  private:
    struct ElementIdRepresentation {
        std::size_t dim : 2;
        std::size_t idx : sizeof(std::size_t) - 2;
    };

    struct Vertex {
        Point2D crd;
        std::optional<std::size_t> incident_edge_idx;
    };

    struct HalfEdge {
        std::size_t origin_idx{};
        std::size_t twin_idx{};
        std::optional<std::size_t> incident_face_idx;
        std::optional<std::size_t> next_idx;
        std::optional<std::size_t> prev_idx;
    };

    struct Edge {
        std::size_t half_edge_1_idx;
        std::size_t half_edge_2_idx;
    };

    struct Face {
        std::size_t incident_edge_idx;
    };

  public:
    using ElementId = std::size_t;

    ElementId addVertex(const Point2D& point);
    ElementId addEdge(ElementId start, ElementId end);
    ElementId addCell(const std::vector<ElementId>& edges);

    [[nodiscard]] const Point2D& vertexPoint(ElementId vertex) const;
    [[nodiscard]] std::pair<ElementId, ElementId> edgeVertices(
        ElementId edge) const;
    [[nodiscard]] std::vector<ElementId> cellFaces(ElementId cell,
                                                   std::size_t dim) const;

    [[nodiscard]] std::vector<ElementId> vertices() const;
    [[nodiscard]] std::vector<ElementId> edges() const;
    [[nodiscard]] std::vector<ElementId> cells(std::size_t dim) const;

  private:
    std::vector<Vertex> vertices_;
    std::vector<HalfEdge> half_edges_;
    std::vector<Edge> edges_;
    std::vector<Face> faces_;
};

}  // namespace vdg

#endif  // VDG_TOPOLOGICALVORONOIDIAGRAM_DCELVORONOIDIAGRAM_H
