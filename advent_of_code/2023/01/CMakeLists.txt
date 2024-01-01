add_executable(aoc_2023_01 solution.cpp)

configure_file(example.txt example.txt)
configure_file(example_b.txt example_b.txt)
configure_file(input.txt input.txt)

add_aoc_python_solution(aoc_2023_01_py)
