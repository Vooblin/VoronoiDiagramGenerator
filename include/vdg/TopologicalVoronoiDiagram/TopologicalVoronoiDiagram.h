#ifndef VDG_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM_H
#define VDG_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM_H

#include <vdg/HasElementId.h>

#include <concepts>
#include <type_traits>
#include <vector>

namespace vdg {

template<typename TDiagram, typename TPoint>
concept TopologicalVoronoiDiagram =
    HasElementId<TDiagram> && std::is_default_constructible_v<TDiagram> &&
    requires(TDiagram diagram,
             TPoint point,
             typename TDiagram::ElementId elem_id,
             std::vector<typename TDiagram::ElementId> elem_ids,
             std::size_t dim) {
        {
            diagram.addVertex(point)
        } -> std::same_as<typename TDiagram::ElementId>;
        {
            diagram.addEdge(elem_id, elem_id)
        } -> std::same_as<typename TDiagram::ElementId>;
        {
            diagram.addCell(elem_ids)
        } -> std::same_as<typename TDiagram::ElementId>;
        { diagram.vertexPoint(elem_id) } -> std::same_as<const TPoint&>;
        {
            diagram.edgeVertices(elem_id)
        } -> std::same_as<std::pair<typename TDiagram::ElementId,
                                    typename TDiagram::ElementId>>;
        {
            diagram.cellFaces(elem_id, dim)
        } -> std::same_as<std::vector<typename TDiagram::ElementId>>;
        {
            diagram.vertices()
        } -> std::same_as<std::vector<typename TDiagram::ElementId>>;
        {
            diagram.edges()
        } -> std::same_as<std::vector<typename TDiagram::ElementId>>;
        {
            diagram.cells(dim)
        } -> std::same_as<std::vector<typename TDiagram::ElementId>>;
    };

}  // namespace vdg

#endif  // VDG_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM_H
