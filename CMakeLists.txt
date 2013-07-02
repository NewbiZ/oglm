CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(matrix)

INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-march=native)

ADD_EXECUTABLE(matrix src/main.cpp src/matrix.cpp)
