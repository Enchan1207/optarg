#
# examples
#
cmake_minimum_required(VERSION 3.21)

add_executable(example_flex example_flex.c)
target_link_libraries(example_flex optarg)

include_directories(${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})
