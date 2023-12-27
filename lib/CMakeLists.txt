# Google test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14
        FIND_PACKAGE_ARGS NAMES GTest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(moszir_lib INTERFACE)
target_include_directories(moszir_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/moszir_lib)

add_subdirectory(moszir_lib_tests)
