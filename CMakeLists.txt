cmake_minimum_required(VERSION 3.10)

project(LibrariesExample VERSION 1.0
                               DESCRIPTION "A simple example of libraries"
                               LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_subdirectory(external/mystaticlib)
add_subdirectory(external/mydllib)

add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE mystaticlib mydllib)
