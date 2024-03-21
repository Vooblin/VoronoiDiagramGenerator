#ifndef VDG_SITE_POINTSITE_H
#define VDG_SITE_POINTSITE_H

#include <vdg/DistanceFunction.h>

#include <utility>

namespace vdg {

template<typename TPoint>
class PointSite {
  public:
    explicit PointSite(TPoint point) noexcept : point_(std::move(point)) {}

    template<DistanceFunction<TPoint> TFunction>
    [[nodiscard]] double distance(const TPoint& point,
                                  const TFunction& func) const {
        return func(point_, point);
    }

  private:
    TPoint point_;
};

}  // namespace vdg

#endif  // VDG_SITE_POINTSITE_H
