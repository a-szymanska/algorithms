cmake_minimum_required(VERSION 3.25)
project(algorithms)

set(CMAKE_CXX_STANDARD 20)


enable_testing()
add_subdirectory(tests)


add_executable(test_algebra tests/algebra.cpp)
target_link_libraries(elliptic_curve gmp gmpxx)

add_executable(test_dynamic tests/dynamic.cpp)

add_executable(test_geometry tests/geometry.cpp)

add_executable(test_graph tests/graph.cpp)

add_executable(test_matrix tests/matrix.cpp)

add_executable(test_number tests/number.cpp)
add_executable(simplex number/simplex.cpp number/simplex.hpp)

add_executable(test_sorting tests/sorting.cpp)

add_executable(double_list structures/double_linked_list.cpp structures/double_linked_list.hpp)
add_executable(interval_tree structures/interval_tree.cpp structures/interval_tree.hpp)
add_executable(unordered_map structures/unordered_map.cpp structures/unordered_map.hpp)
add_executable(heap structures/heap.cpp structures/heap.hpp)

add_executable(test_text tests/texts.cpp)
