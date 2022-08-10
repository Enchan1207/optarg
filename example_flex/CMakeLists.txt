#
# example_flex
#
cmake_minimum_required(VERSION 3.21)

# generate testcases
add_executable(example_flex
    example.c
)
target_link_libraries(example_flex
    optarg
)
include_directories(${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})
