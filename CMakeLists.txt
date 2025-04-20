cmake_minimum_required(VERSION 3.22)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Main
        src/main.cpp
        src/Song.cpp
        src/mergeSort.h
        src/quickSort.h
)
