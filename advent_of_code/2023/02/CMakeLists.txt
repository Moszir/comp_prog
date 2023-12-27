add_executable(aoc_2023_02 solution.cpp)
target_link_libraries(aoc_2023_02 PRIVATE moszir_lib)

configure_file(example.txt example.txt)
configure_file(input.txt input.txt)
