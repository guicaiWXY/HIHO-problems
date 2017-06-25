cmake_minimum_required(VERSION 3.6)
project(HIHO-problems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp problem.cpp problem.h
#        weekly-challenges/week154.cpp weekly-challenges/week154.h
         weekly-challenges/week155.cpp weekly-challenges/week155.h
#        weekly-challenges/week154_AC1.cpp weekly-challenges/week154_AC1.h
#        coding-challenges/ms_6_17_p1.cpp
#        coding-challenges/ms_6_17_p2.cpp
#        problem-set/_1015_kmp.h
#        problem-set/_1015_kmp.cpp
#        problem-set/_1015_kmp_AC1.cpp
#        problem-set/_1015_kmp_AC2.cpp
        )
add_executable(HIHO-problems ${SOURCE_FILES})