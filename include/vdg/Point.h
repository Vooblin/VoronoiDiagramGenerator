#ifndef VDG_POINT_H
#define VDG_POINT_H

#include <array>
#include <vector>

namespace vdg {

template<std::size_t N>
using PointND = std::array<double, N>;
using Point2D = PointND<2>;
using Point3D = PointND<3>;

using PointXD = std::vector<double>;

}  // namespace vdg

#endif  // VDG_POINT_H
