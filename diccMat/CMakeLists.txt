cmake_minimum_required(VERSION 3.5)
project(diccMat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/aed2/Arreglo.h
    src/aed2/Conj.h
    src/aed2/ConjAcotado.cpp
    src/aed2/ConjAcotado.h
    src/aed2/Dicc.h
    src/aed2/Lista.h
    src/aed2/TiposBasicos.h
    src/aed2/Vector.h
    src/DiccMat.hpp
    src/Lista.h
    src/mini_test.h
    src/test_dhc.cpp
    src/TiposBasicos.h)

add_executable(diccMat ${SOURCE_FILES})