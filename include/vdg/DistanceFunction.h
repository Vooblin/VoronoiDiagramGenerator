#ifndef VDG_DISTANCEFUNCTION_H
#define VDG_DISTANCEFUNCTION_H

#include <concepts>

namespace vdg {

template<typename TFunction, typename TPoint>
concept DistanceFunction = requires(TFunction func, TPoint lhs, TPoint rhs) {
    { func(lhs, rhs) } -> std::convertible_to<double>;
};

}  // namespace vdg

#endif  // VDG_DISTANCEFUNCTION_H
