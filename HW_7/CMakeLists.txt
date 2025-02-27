cmake_minimum_required(VERSION 3.29)
project(AVLTree)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AVLTreeTests tests.cpp)

target_link_libraries(AVLTreeTests ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME AVLTreeTest COMMAND AVLTreeTests)
