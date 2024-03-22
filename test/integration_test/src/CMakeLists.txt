add_executable(vdg_integration_tests Site/PointSiteEuclideanDistanceTest.cpp)
target_include_directories(
  vdg_integration_tests PUBLIC ${VDG_INCLUDE_DIR} ${VDG_TEST_INCLUDE_DIR}
                               ${VDG_INTEGRATION_TEST_INCLUDE_DIR})
target_link_libraries(vdg_integration_tests PUBLIC gtest_main gmock_main)
