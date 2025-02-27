cmake_minimum_required(VERSION 3.29)
project(biginteger)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(Biginteger STATIC biginteger.cpp)

add_executable(BigintegerTests tests.cpp)

target_link_libraries(BigintegerTests ${GTEST_LIBRARIES} Biginteger)

enable_testing()
add_test(NAME BigintegerTest COMMAND BigintegerTests)
