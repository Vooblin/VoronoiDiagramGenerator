#ifndef VDG_SITE_SITE_H
#define VDG_SITE_SITE_H

#include <vdg/DistanceFunction/DistanceFunction.h>

#include <concepts>

namespace vdg {

template<typename TSite, typename TPoint, typename TFunction>
concept Site = DistanceFunction<TFunction, TPoint> &&
               requires(TSite site, TPoint point, TFunction func) {
                   { site.distance(point, func) } -> std::same_as<double>;
               };

}  // namespace vdg

#endif  // VDG_SITE_SITE_H
