cmake_minimum_required(VERSION 3.24)
project(day7)

set(CMAKE_CXX_STANDARD 17)

add_executable(day7 main.cpp solver.cpp solver.h utils.cpp utils.h hand.cpp hand.h)
