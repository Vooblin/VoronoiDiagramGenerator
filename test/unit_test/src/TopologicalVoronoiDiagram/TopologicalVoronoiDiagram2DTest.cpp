#include <vdg/Point.h>
#include <vdg/TopologicalVoronoiDiagram.h>
#include <vdg/TopologicalVoronoiDiagram/DcelVoronoiDiagram.h>

#include <gtest/gtest.h>

#include <TopologicalVoronoiDiagram/TopologicalVoronoiDiagram2DTest.h>

namespace vdg::test {

using TopologicalVoronoiDiagram2DTestTypes =
    ::testing::Types<DcelVoronoiDiagram>;
TYPED_TEST_SUITE(TopologicalVoronoiDiagram2DTest,
                 TopologicalVoronoiDiagram2DTestTypes);

TYPED_TEST(TopologicalVoronoiDiagram2DTest, ConceptTest) {
    static_assert(TopologicalVoronoiDiagram<TypeParam, Point2D>);
}

}  // namespace vdg::test
