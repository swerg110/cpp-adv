cmake_minimum_required(VERSION 3.29)
project(FormatTests)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(FormatTests tests.cpp)

target_link_libraries(FormatTests ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME FormatTest COMMAND FormatTests)
