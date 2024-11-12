cmake_minimum_required(VERSION 3.15)

project(mylib VERSION 1.0
              DESCRIPTION "Simple Library that adds math functions"  
              LANGUAGES CXX)

add_library(mylib mylib.cpp)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})