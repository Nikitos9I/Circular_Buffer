cmake_minimum_required(VERSION 3.9)
project(Circular_Buffer)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_executable(Circular_Buffer
        my_circular_buffer.cpp
        my_circular_buffer.h
        my_circular_buffer_testing.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)
