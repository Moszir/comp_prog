function(add_aoc_python_solution test_name)
    add_test(
        NAME ${test_name}
        COMMAND ${Python_EXECUTABLE} -m unittest "${CMAKE_CURRENT_SOURCE_DIR}/solution.py"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    set_tests_properties(${test_name} PROPERTIES LABELS "moszir;python;aoc")
endfunction()

add_subdirectory(2023)
