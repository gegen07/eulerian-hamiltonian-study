cmake_minimum_required(VERSION 3.22)
project(tp2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(LIB_DIRECTORY lib)

set(SOURCES_LIST
        ${LIB_DIRECTORY}/doubly-linked-list.hpp
        ${LIB_DIRECTORY}/list.hpp
        ${LIB_DIRECTORY}/graph-adj-list.hpp
        ${LIB_DIRECTORY}/graph-adj-matrix.hpp
        ${LIB_DIRECTORY}/graph-incidency-matrix.hpp
        ${LIB_DIRECTORY}/graph.hpp)

add_executable(tp2 main.cpp ${SOURCES_LIST})

target_include_directories (tp2 PRIVATE ${SOURCES_LIST})