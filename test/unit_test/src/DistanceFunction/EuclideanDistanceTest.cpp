#include <vdg/DistanceFunction/EuclideanDistance.h>
#include <vdg/Point.h>

#include <gtest/gtest.h>

#include <cmath>

namespace vdg::test {

TEST(EuclideanDistanceTest, Point2DTest) {
    const EuclideanDistance<Point2D> distance;
    const Point2D lhs{1, 2};
    const Point2D rhs{3, 4};
    const double expected = std::sqrt(8);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(EuclideanDistanceTest, Point3DTest) {
    const EuclideanDistance<Point3D> distance;
    const Point3D lhs{1, 2, 3};
    const Point3D rhs{4, 5, 6};
    const double expected = std::sqrt(27);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(EuclideanDistanceTest, PointXDTest) {
    const EuclideanDistance<PointXD> distance;
    const PointXD lhs{1, 2, 3, 4};
    const PointXD rhs{5, 6, 7, 8};
    const double expected = std::sqrt(64);
    const double actual = distance(lhs, rhs);
    EXPECT_DOUBLE_EQ(expected, actual);
}

}  // namespace vdg::test
