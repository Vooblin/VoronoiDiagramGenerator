cmake_minimum_required(VERSION 3.28)

project(
  VoronoiDiagramGenerator
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_UNITY_BUILD ON)
  set(CMAKE_UNITY_BUILD_BATCH_SIZE 128)
endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  set(VDG_ROOT ON)
else()
  set(VDG_ROOT OFF)
endif()

add_subdirectory(submodule)

if(${VDG_ROOT} AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
endif()

if(${CODE_COVERAGE})
  add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
  add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()

set(VDG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)

if(${VDG_ROOT})
  add_subdirectory(test)
  add_subdirectory(example)
  add_subdirectory(benchmark)
endif()
