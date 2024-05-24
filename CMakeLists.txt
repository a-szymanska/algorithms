cmake_minimum_required(VERSION 3.25)
project(algorithms)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithms_sorting sorting/test.cpp)
add_executable(algorithms_numbers numbers/test.cpp)
add_executable(algorithms_graphs graphs/test.cpp)
add_executable(algorithms_geometry geometry/test.cpp)
add_executable(double_list structures/double_linked_list.cpp structures/double_linked_list.h)