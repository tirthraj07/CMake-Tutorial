cmake_minimum_required(VERSION 3.15)    # This line specifies that CMake 3.15 or later is required to build the project.


project(NewCMakeProject VERSION 1.0
                        DESCRIPTION "Very First CMake Project"
                        LANGUAGES CXX)

# The project command defines:
# The project name (NewCMakeProject),
# The version (1.0),
# A description ("Very First CMake Project"), and
# The language (CXX, which is for C++).

add_executable(${PROJECT_NAME} main.cpp)