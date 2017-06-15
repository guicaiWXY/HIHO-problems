cmake_minimum_required(VERSION 3.6)
project(HIHO-problems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp problem.cpp problem.h
        weekly-challenges/week154.cpp weekly-challenges/week154.h
        )
add_executable(HIHO-problems ${SOURCE_FILES})