cmake_minimum_required(VERSION 3.29)
project(TokenParser)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(TokenParser STATIC tokenParser.cpp)

add_executable(TokenParserTests tokenParserTests.cpp)

target_link_libraries(TokenParserTests ${GTEST_LIBRARIES} TokenParser)

enable_testing()
add_test(NAME tokenParserTest COMMAND tokenParserTests)