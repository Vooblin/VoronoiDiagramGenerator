#include <vdg/DistanceFunction/EuclideanDistance.h>
#include <vdg/Point.h>
#include <vdg/Site/PointSite.h>
#include <vdg/Site/Site.h>

#include <gtest/gtest.h>

#include <cmath>

namespace vdg::test {

static_assert(Site<PointSite<Point2D>, Point2D, EuclideanDistance>);
static_assert(Site<PointSite<Point3D>, Point3D, EuclideanDistance>);
static_assert(Site<PointSite<PointXD>, PointXD, EuclideanDistance>);

TEST(PointSiteEuclideanDistanceTest, Point2DTest) {
    const PointSite<Point2D> site(Point2D{1, 2});
    const Point2D point{3, 4};
    const EuclideanDistance func;
    const double expected = std::sqrt(8);
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(PointSiteEuclideanDistanceTest, Point3DTest) {
    const PointSite<Point3D> site(Point3D{1, 2, 3});
    const Point3D point{4, 5, 6};
    const EuclideanDistance func;
    const double expected = std::sqrt(27);
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(PointSiteEuclideanDistanceTest, PointXDTest) {
    const PointSite<PointXD> site(PointXD{1, 2, 3, 4});
    const PointXD point{5, 6, 7, 8};
    const EuclideanDistance func;
    const double expected = std::sqrt(64);
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

}  // namespace vdg::test
