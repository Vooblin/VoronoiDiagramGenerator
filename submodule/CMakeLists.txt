if(${VDG_ROOT})
  include(FetchContent)
  if(NOT TARGET benchmark::benchmark)
    set(BENCHMARK_ENABLE_TESTING
        OFF
        CACHE BOOL "Override option" FORCE)
    FetchContent_Declare(
      benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_SHALLOW ON
      GIT_PROGRESS ON
      GIT_TAG v1.8.3)
    FetchContent_MakeAvailable(benchmark)
  endif()

  # For Windows: Prevent overriding the parent project's compiler/linker
  # settings
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_SHALLOW ON
    GIT_PROGRESS ON
    GIT_TAG v1.14.0)
  FetchContent_MakeAvailable(googletest)
endif()
