#include <vdg/DistanceFunction/DistanceFunction.h>
#include <vdg/DistanceFunction/EuclideanDistance.h>
#include <vdg/Point.h>

#include <gtest/gtest.h>

#include <cmath>

namespace vdg::test {

static_assert(DistanceFunction<EuclideanDistance, Point2D>);
static_assert(DistanceFunction<EuclideanDistance, Point3D>);
static_assert(DistanceFunction<EuclideanDistance, PointXD>);

TEST(EuclideanDistanceTest, Point2DTest) {
    const EuclideanDistance distance;
    const Point2D lhs{1, 2};
    const Point2D rhs{3, 4};
    const double expected = std::sqrt(8);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(EuclideanDistanceTest, Point3DTest) {
    const EuclideanDistance distance;
    const Point3D lhs{1, 2, 3};
    const Point3D rhs{4, 5, 6};
    const double expected = std::sqrt(27);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(EuclideanDistanceTest, PointXDTest) {
    const EuclideanDistance distance;
    const PointXD lhs{1, 2, 3, 4};
    const PointXD rhs{5, 6, 7, 8};
    const double expected = std::sqrt(64);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

}  // namespace vdg::test
