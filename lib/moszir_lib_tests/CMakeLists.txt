include(GoogleTest)

function(add_moszir_test name)
    add_executable(${name}_test ${name}_test.cpp)
    target_link_libraries(${name}_test gtest gtest_main moszir_lib)
    gtest_discover_tests(${name}_test PROPERTIES LABELS "moszir")
endfunction()

set(STRING_TESTS "string_conversions;string_vector;string_view_vector")
set(MATH_TESTS "modular_integer")
foreach(name IN LISTS STRING_TESTS MATH_TESTS)
    add_moszir_test(${name})
endforeach ()


add_executable(string_split_benchmark "string_split_benchmark.cpp")
target_link_libraries(string_split_benchmark benchmark::benchmark moszir_lib)
