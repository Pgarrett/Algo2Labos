cmake_minimum_required(VERSION 3.6)
project(taller6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    data/gauss.txt
    data/libretas.txt
    data/uniforme.txt
    src/DiccHashCerrado.hpp
    src/Lista.h
    src/mini_test.h
    src/test_dhc.cpp
    src/TiposBasicos.h)

add_executable(taller6 ${SOURCE_FILES})