#ifndef VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM2DTEST_H
#define VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM2DTEST_H

#include <gtest/gtest.h>

namespace vdg::test {

template<typename TDiagram>
class TopologicalVoronoiDiagram2DTest : public ::testing::Test {
  protected:
    TopologicalVoronoiDiagram2DTest() = default;
};

}  // namespace vdg::test

#endif  // VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAM_TOPOLOGICALVORONOIDIAGRAM2DTEST_H
