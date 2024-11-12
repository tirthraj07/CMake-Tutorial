cmake_minimum_required(VERSION 3.15)

project(ExternalLibraries VERSION 1.0
                          DESCRIPTION "An example of using external libraries in C++"
                          LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
                           PUBLIC external/glfw/include/
)

target_link_directories(${PROJECT_NAME} 
                        PRIVATE external/glfw/src/
)

# Link against both glfw and OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} 
                      glfw
                      OpenGL::GL
)
