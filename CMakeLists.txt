cmake_minimum_required(VERSION 3.6)
project(base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Conjunto.hpp
    tests.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(base ${SOURCE_FILES})
add_executable(runTests tests.cpp Conjunto.hpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)