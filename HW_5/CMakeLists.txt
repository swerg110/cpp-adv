cmake_minimum_required(VERSION 3.29)
project(SerializerProject)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES tests.cpp)

add_executable(serializer_test ${SOURCES})

find_package(GTest REQUIRED)
target_link_libraries(serializer_test GTest::gtest GTest::gtest_main)


add_test(NAME SerializerTest COMMAND serializer_test)
