#
# optarg
#
cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 11)

project(optarg LANGUAGES C CXX)

enable_testing()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
