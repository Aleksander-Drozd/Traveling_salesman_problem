cmake_minimum_required(VERSION 3.6)
project(Traveling_Salesman_problem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Sources/main.cpp Sources/SalesmanProblem.cpp Headers/SalesmanProblem.h)
add_executable(Traveling_Salesman_problem ${SOURCE_FILES})