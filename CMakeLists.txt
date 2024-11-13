cmake_minimum_required(VERSION 3.15)

project(ExternalLibraries VERSION 1.0
                          DESCRIPTION "An example of using external libraries in C++"
                          LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

# Add glfw as a subdirectory
add_subdirectory(external/glfw)

# Link against both glfw and OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} 
                      PRIVATE glfw
                      PRIVATE OpenGL::GL
)
