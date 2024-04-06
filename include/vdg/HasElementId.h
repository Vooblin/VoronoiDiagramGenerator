#ifndef VDG_HASELEMENTID_H
#define VDG_HASELEMENTID_H

#include <concepts>

namespace vdg {

template<typename TObject>
concept HasElementId = requires {
    typename TObject::ElementId;
    requires std::equality_comparable<typename TObject::ElementId>;
};

}  // namespace vdg

#endif  // VDG_HASELEMENTID_H
