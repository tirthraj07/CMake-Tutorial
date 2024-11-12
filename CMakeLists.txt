cmake_minimum_required(VERSION 3.15)

project(MyProject VERSION 1.0
                  DESCRIPTION "Project that showcases Static libraries in C++"
                  LANGUAGES CXX)


add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE mylib)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)