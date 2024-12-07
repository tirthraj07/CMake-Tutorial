cmake_minimum_required(VERSION 3.10)

project(mystaticlib)

add_library(mystaticlib STATIC
    lib/staticlib.cpp
    includes/staticlib.h
)


target_include_directories(mystaticlib PUBLIC includes)