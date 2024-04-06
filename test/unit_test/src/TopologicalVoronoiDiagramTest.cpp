#include <TopologicalVoronoiDiagramTest.h>

#include <vdg/Point.h>
#include <vdg/TopologicalVoronoiDiagram/DcelVoronoiDiagram.h>
#include <vdg/TopologicalVoronoiDiagram/TopologicalVoronoiDiagram.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

namespace vdg::test {

using TopologicalVoronoiDiagram2DTestTypes =
    ::testing::Types<DcelVoronoiDiagram>;
TYPED_TEST_SUITE(TopologicalVoronoiDiagram2DTest,
                 TopologicalVoronoiDiagram2DTestTypes);

TYPED_TEST(TopologicalVoronoiDiagram2DTest, ConceptTest) {
    static_assert(TopologicalVoronoiDiagram<TypeParam, Point2D>);
}

template<typename TPoint>
void testPointEquality(const TPoint& expected, const TPoint& actual) {
    ASSERT_EQ(expected.size(), actual.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        EXPECT_DOUBLE_EQ(expected.at(i), actual.at(i));
    }
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, OneVertexTest) {
    TypeParam diagram;
    const Point2D point{1, 2};
    auto elem_id = diagram.addVertex(point);

    testPointEquality(point, diagram.vertexPoint(elem_id));

    ASSERT_EQ(diagram.vertices().size(), 1);
    EXPECT_EQ(diagram.vertices().at(0), elem_id);
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, TwoVerticesTest) {
    TypeParam diagram;
    const Point2D point1{1, 2};
    const Point2D point2{3, 4};
    auto elem_id1 = diagram.addVertex(point1);
    auto elem_id2 = diagram.addVertex(point2);

    testPointEquality(point1, diagram.vertexPoint(elem_id1));
    testPointEquality(point2, diagram.vertexPoint(elem_id2));

    ASSERT_EQ(diagram.vertices().size(), 2);
    auto v1 = diagram.vertices().at(0);
    auto v2 = diagram.vertices().at(1);
    EXPECT_EQ(std::min(v1, v2), std::min(elem_id1, elem_id2));
    EXPECT_EQ(std::max(v1, v2), std::max(elem_id1, elem_id2));
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, OneEdgeTest) {
    TypeParam diagram;
    const Point2D point1{1, 2};
    const Point2D point2{3, 4};
    auto elem_id1 = diagram.addVertex(point1);
    auto elem_id2 = diagram.addVertex(point2);
    auto edge_id = diagram.addEdge(elem_id1, elem_id2);

    auto [v1, v2] = diagram.edgeVertices(edge_id);
    EXPECT_EQ(std::min(v1, v2), std::min(elem_id1, elem_id2));
    EXPECT_EQ(std::max(v1, v2), std::max(elem_id1, elem_id2));

    ASSERT_EQ(diagram.edges().size(), 1);
    EXPECT_EQ(diagram.edges().at(0), edge_id);
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, TwoEdgesTest) {
    TypeParam diagram;
    const Point2D point1{1, 2};
    const Point2D point2{3, 4};
    const Point2D point3{5, 6};
    auto elem_id1 = diagram.addVertex(point1);
    auto elem_id2 = diagram.addVertex(point2);
    auto elem_id3 = diagram.addVertex(point3);
    auto edge_id1 = diagram.addEdge(elem_id1, elem_id2);
    auto edge_id2 = diagram.addEdge(elem_id2, elem_id3);

    auto [v1, v2] = diagram.edgeVertices(edge_id1);
    EXPECT_EQ(std::min(v1, v2), std::min(elem_id1, elem_id2));
    EXPECT_EQ(std::max(v1, v2), std::max(elem_id1, elem_id2));
    auto [v3, v4] = diagram.edgeVertices(edge_id2);
    EXPECT_EQ(std::min(v3, v4), std::min(elem_id2, elem_id3));
    EXPECT_EQ(std::max(v3, v4), std::max(elem_id2, elem_id3));

    ASSERT_EQ(diagram.edges().size(), 2);
    auto e1 = diagram.edges().at(0);
    auto e2 = diagram.edges().at(1);
    EXPECT_EQ(std::min(e1, e2), std::min(edge_id1, edge_id2));
    EXPECT_EQ(std::max(e1, e2), std::max(edge_id1, edge_id2));
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, OneFaceTest) {
    TypeParam diagram;
    const Point2D point1{1, 2};
    const Point2D point2{3, 4};
    const Point2D point3{5, 6};
    auto elem_id1 = diagram.addVertex(point1);
    auto elem_id2 = diagram.addVertex(point2);
    auto elem_id3 = diagram.addVertex(point3);
    auto edge_id1 = diagram.addEdge(elem_id1, elem_id2);
    auto edge_id2 = diagram.addEdge(elem_id2, elem_id3);
    auto edge_id3 = diagram.addEdge(elem_id3, elem_id1);
    auto face_id = diagram.addCell({edge_id1, edge_id2, edge_id3});

    std::vector<typename TypeParam::ElementId> expected_face_edges{
        edge_id1, edge_id2, edge_id3};
    auto actual_face_edges = diagram.cellFaces(face_id, 1);
    ASSERT_EQ(actual_face_edges.size(), 3);
    std::sort(expected_face_edges.begin(), expected_face_edges.end());
    std::sort(actual_face_edges.begin(), actual_face_edges.end());
    EXPECT_EQ(expected_face_edges, actual_face_edges);

    std::vector<typename TypeParam::ElementId> expected_face_vertices{
        elem_id1, elem_id2, elem_id3};
    auto actual_face_vertices = diagram.cellFaces(face_id, 0);
    ASSERT_EQ(actual_face_vertices.size(), 3);
    std::sort(expected_face_vertices.begin(), expected_face_vertices.end());
    std::sort(actual_face_vertices.begin(), actual_face_vertices.end());
    EXPECT_EQ(expected_face_vertices, actual_face_vertices);

    ASSERT_EQ(diagram.cells(2).size(), 1);
    EXPECT_EQ(diagram.cells(2).at(0), face_id);
}

TYPED_TEST(TopologicalVoronoiDiagram2DTest, TwoFacesTest) {
    TypeParam diagram;
    const Point2D point1{1, 2};
    const Point2D point2{3, 4};
    const Point2D point3{5, 6};
    const Point2D point4{7, 8};
    auto elem_id1 = diagram.addVertex(point1);
    auto elem_id2 = diagram.addVertex(point2);
    auto elem_id3 = diagram.addVertex(point3);
    auto elem_id4 = diagram.addVertex(point4);
    auto edge_id1 = diagram.addEdge(elem_id1, elem_id2);
    auto edge_id2 = diagram.addEdge(elem_id2, elem_id3);
    auto edge_id3 = diagram.addEdge(elem_id3, elem_id1);
    auto edge_id4 = diagram.addEdge(elem_id2, elem_id4);
    auto edge_id5 = diagram.addEdge(elem_id4, elem_id1);
    auto face_id1 = diagram.addCell({edge_id1, edge_id2, edge_id3});
    auto face_id2 = diagram.addCell({edge_id1, edge_id4, edge_id5});

    std::vector<typename TypeParam::ElementId> expected_face1_edges{
        edge_id1, edge_id2, edge_id3};
    auto actual_face1_edges = diagram.cellFaces(face_id1, 1);
    ASSERT_EQ(actual_face1_edges.size(), 3);
    std::sort(expected_face1_edges.begin(), expected_face1_edges.end());
    std::sort(actual_face1_edges.begin(), actual_face1_edges.end());
    EXPECT_EQ(expected_face1_edges, actual_face1_edges);

    std::vector<typename TypeParam::ElementId> expected_face1_vertices{
        elem_id1, elem_id2, elem_id3};
    auto actual_face1_vertices = diagram.cellFaces(face_id1, 0);
    ASSERT_EQ(actual_face1_vertices.size(), 3);
    std::sort(expected_face1_vertices.begin(), expected_face1_vertices.end());
    std::sort(actual_face1_vertices.begin(), actual_face1_vertices.end());
    EXPECT_EQ(expected_face1_vertices, actual_face1_vertices);

    std::vector<typename TypeParam::ElementId> expected_face2_edges{
        edge_id1, edge_id4, edge_id5};
    auto actual_face2_edges = diagram.cellFaces(face_id2, 1);
    ASSERT_EQ(actual_face2_edges.size(), 3);
    std::sort(expected_face2_edges.begin(), expected_face2_edges.end());
    std::sort(actual_face2_edges.begin(), actual_face2_edges.end());
    EXPECT_EQ(expected_face2_edges, actual_face2_edges);

    std::vector<typename TypeParam::ElementId> expected_face2_vertices{
        elem_id1, elem_id2, elem_id4};
    auto actual_face2_vertices = diagram.cellFaces(face_id2, 0);
    ASSERT_EQ(actual_face2_vertices.size(), 3);
    std::sort(expected_face2_vertices.begin(), expected_face2_vertices.end());
    std::sort(actual_face2_vertices.begin(), actual_face2_vertices.end());
    EXPECT_EQ(expected_face2_vertices, actual_face2_vertices);

    ASSERT_EQ(diagram.cells(2).size(), 2);
    auto f1 = diagram.cells(2).at(0);
    auto f2 = diagram.cells(2).at(1);
    EXPECT_EQ(std::min(f1, f2), std::min(face_id1, face_id2));
    EXPECT_EQ(std::max(f1, f2), std::max(face_id1, face_id2));
}

}  // namespace vdg::test
