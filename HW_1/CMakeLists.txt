cmake_minimum_required(VERSION 3.29)
project(allocatorProject)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(allocator STATIC allocator.cpp)

add_executable(allocator_test allocator_test.cpp)
target_link_libraries(allocator_test allocator GTest::GTest GTest::Main)

enable_testing()
add_test(NAME AllocatorTest COMMAND allocator_test)