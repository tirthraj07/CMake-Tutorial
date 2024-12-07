cmake_minimum_required(VERSION 3.10)

project(SharedLibsPy VERSION 1.0
					 DESCRIPTION "A Project demonstrating use of shared libs with Python"
					 LANGUAGES CXX
)

add_library(mylib SHARED 
	src/mylib.cpp 
	includes/mylib.h
)

target_include_directories(mylib PUBLIC includes)
