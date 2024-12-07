cmake_minimum_required(VERSION 3.10)

# Set the project name for the dynamic library
project(mydllib)

# Add the shared library target
add_library(mydllib SHARED
    lib/dllib.cpp
    includes/dllib.h
)

# Specify the include directories
target_include_directories(mydllib PUBLIC includes)
