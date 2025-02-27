cmake_minimum_required(VERSION 3.29)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(Matrix STATIC matrix.cpp)

add_executable(MatrixTests tests.cpp)

target_link_libraries(MatrixTests ${GTEST_LIBRARIES} Matrix)

enable_testing()
add_test(NAME MatrixTest COMMAND MatrixTests)
