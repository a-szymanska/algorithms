cmake_minimum_required(VERSION 3.25)
project(algorithms)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

# ---------------------------
# Tests
# ---------------------------
add_executable(test_algebra tests/algebra.cpp)
add_test(NAME AlgebraTests COMMAND test_algebra)

add_executable(test_dynamic tests/dynamic.cpp)
add_test(NAME DynamicTests COMMAND test_dynamic)

add_executable(test_geometry tests/geometry.cpp)
add_test(NAME GeometryTests COMMAND test_geometry)

add_executable(test_graph tests/graph.cpp)
add_test(NAME GraphTests COMMAND test_graph)

add_executable(test_matrix tests/matrix.cpp)
add_test(NAME MatrixTests COMMAND test_matrix)

add_executable(test_number tests/number.cpp)
add_test(NAME NumberTests COMMAND test_number)

add_executable(test_sorting tests/sorting.cpp)
add_test(NAME SortingTests COMMAND test_sorting)

add_executable(test_text tests/texts.cpp)
add_test(NAME TextTests COMMAND test_text)

# ---------------------------
# Other
# ---------------------------
add_executable(simplex number/simplex.cpp)
add_executable(double_list structures/double_linked_list.cpp)
add_executable(interval_tree structures/interval_tree.cpp)
add_executable(unordered_map structures/unordered_map.cpp)
add_executable(heap structures/heap.cpp)
