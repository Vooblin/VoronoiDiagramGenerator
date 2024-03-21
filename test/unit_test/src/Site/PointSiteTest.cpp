#include <vdg/Point.h>
#include <vdg/Site.h>
#include <vdg/Site/PointSite.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mock/DistanceFunctionMock.h>
#include <stub/DistanceFunctionStub.h>

namespace vdg::test {

static_assert(Site<PointSite<Point2D>, Point2D, DistanceFunctionStub<Point2D>>);
static_assert(Site<PointSite<Point3D>, Point3D, DistanceFunctionStub<Point3D>>);
static_assert(Site<PointSite<PointXD>, PointXD, DistanceFunctionStub<PointXD>>);

static_assert(Site<PointSite<Point2D>, Point2D, DistanceFunctionMock<Point2D>>);
static_assert(Site<PointSite<Point3D>, Point3D, DistanceFunctionMock<Point3D>>);
static_assert(Site<PointSite<PointXD>, PointXD, DistanceFunctionMock<PointXD>>);

TEST(PointSiteTest, Point2DStubTest) {
    const PointSite<Point2D> site(Point2D{1, 2});
    const Point2D point{3, 4};
    const DistanceFunctionStub<Point2D> func;
    const double expected = 0;
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(PointSiteTest, Point3DStubTest) {
    const PointSite<Point3D> site(Point3D{1, 2, 3});
    const Point3D point{4, 5, 6};
    const DistanceFunctionStub<Point3D> func;
    const double expected = 0;
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(PointSiteTest, PointXDStubTest) {
    const PointSite<PointXD> site(PointXD{1, 2, 3, 4});
    const PointXD point{5, 6, 7, 8};
    const DistanceFunctionStub<PointXD> func;
    const double expected = 0;
    const double actual = site.distance(point, func);
    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST(PointSiteTest, Point2DMockTest) {
    const Point2D site_point{1, 2};
    const PointSite<Point2D> site(site_point);
    const Point2D point{3, 4};
    const DistanceFunctionMock<Point2D> func;
    EXPECT_CALL(func, distance(site_point, point)).WillOnce(testing::Return(0));
    [[maybe_unused]] const double distance = site.distance(point, func);
}

TEST(PointSiteTest, Point3DMockTest) {
    const Point3D site_point{1, 2, 3};
    const PointSite<Point3D> site(site_point);
    const Point3D point{4, 5, 6};
    const DistanceFunctionMock<Point3D> func;
    EXPECT_CALL(func, distance(site_point, point)).WillOnce(testing::Return(0));
    [[maybe_unused]] const double distance = site.distance(point, func);
}

TEST(PointSiteTest, PointXDMockTest) {
    const PointXD site_point{1, 2, 3, 4};
    const PointSite<PointXD> site(site_point);
    const PointXD point{5, 6, 7, 8};
    const DistanceFunctionMock<PointXD> func;
    EXPECT_CALL(func, distance(site_point, point)).WillOnce(testing::Return(0));
    [[maybe_unused]] const double distance = site.distance(point, func);
}

}  // namespace vdg::test
