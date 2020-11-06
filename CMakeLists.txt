cmake_minimum_required(VERSION 3.17)
project(breadth_first_search)
set(CMAKE_CXX_STANDARD 20)


if (MSVC)
    set(CMAKE_CXX_FLAGS std:c++latest)
    else()
    set(CMAKE_CXX_FLAGS -std=c++2a)
endif()
add_executable(breadth_first_search main.cpp)