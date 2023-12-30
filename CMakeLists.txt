cmake_minimum_required(VERSION 3.20)

project(
    competitive_programming
    LANGUAGES CXX
    VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

# =====================================================================================================================
# 3rd party libraries
include(FetchContent)

# Google test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14
        FIND_PACKAGE_ARGS NAMES GTest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Google benchmark
FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG 344117638c8ff7e239044fd0fa7085839fc03021 # release 1.8.3 (2023 August 31)
        FIND_PACKAGE_ARGS NAMES benchmark
)
FetchContent_MakeAvailable(google_benchmark)


add_subdirectory(advent_of_code)
add_subdirectory(contest_sandbox)
add_subdirectory(codechef)
add_subdirectory(codeforces)
add_subdirectory(lib)
add_subdirectory(stl)
