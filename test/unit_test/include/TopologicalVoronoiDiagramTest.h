#ifndef VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAMTEST_H
#define VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAMTEST_H

#include <gtest/gtest.h>

namespace vdg::test {

template<typename TDiagram>
class TopologicalVoronoiDiagramTest : public ::testing::Test {
  protected:
    TopologicalVoronoiDiagramTest() = default;
};

template<typename TDiagram>
class TopologicalVoronoiDiagram2DTest :
    public TopologicalVoronoiDiagramTest<TDiagram> {};

}  // namespace vdg::test

#endif  // VDG_TEST_UNITTEST_TOPOLOGICALVORONOIDIAGRAM_H
