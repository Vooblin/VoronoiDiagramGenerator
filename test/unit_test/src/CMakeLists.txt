add_executable(vdg_unit_tests DistanceFunction/EuclideanDistanceTest.cpp
                              Site/PointSiteTest.cpp)

target_include_directories(
  vdg_unit_tests PUBLIC ${VDG_TEST_INCLUDE_DIR}
                        ${VDG_UNIT_TEST_INCLUDE_DIR})
target_link_libraries(vdg_unit_tests PUBLIC vdg gtest_main gmock_main)
