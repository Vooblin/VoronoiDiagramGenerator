#ifndef VDG_DISTANCEFUNCTION_EUCLIDEANDISTANCE_H
#define VDG_DISTANCEFUNCTION_EUCLIDEANDISTANCE_H

#include <vdg/DistanceFunction.h>
#include <vdg/Point.h>

#include <cassert>
#include <cmath>

namespace vdg {

template<typename TPoint>
class EuclideanDistance {
  public:
    [[nodiscard]] double operator()(const TPoint& lhs,
                                    const TPoint& rhs) const {
        assert(lhs.size() == rhs.size());
        double sum = 0;
        for (std::size_t idx = 0; idx < lhs.size(); ++idx) {
            sum += (lhs.at(idx) - rhs.at(idx)) * (lhs.at(idx) - rhs.at(idx));
        }
        return std::sqrt(sum);
    }
};

static_assert(DistanceFunction<EuclideanDistance<Point2D>, Point2D>);
static_assert(DistanceFunction<EuclideanDistance<Point3D>, Point3D>);
static_assert(DistanceFunction<EuclideanDistance<PointXD>, PointXD>);

}  // namespace vdg

#endif  // VDG_DISTANCEFUNCTION_EUCLIDEANDISTANCE_H
