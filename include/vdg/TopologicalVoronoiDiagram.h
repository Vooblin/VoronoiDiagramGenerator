#ifndef VDG_TOPOLOGICALVORONOIDIAGRAM_H
#define VDG_TOPOLOGICALVORONOIDIAGRAM_H

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
             TDiagram::ElementId elem_id,
             std::vector<typename TDiagram::ElementId> elem_ids) {
        {
            diagram.addVertex(point)
        } -> std::same_as<typename TDiagram::ElementId>;
        {
            diagram.addEdge(elem_id, elem_id)
        } -> std::same_as<typename TDiagram::ElementId>;
        {
            diagram.addCell(elem_ids)
        } -> std::same_as<typename TDiagram::ElementId>;
    };

}  // namespace vdg

#endif  // VDG_TOPOLOGICALVORONOIDIAGRAM_H
