cmake_minimum_required(VERSION 3.18)

project(ComputerGraphics VERSION 1.0
                         DESCRIPTION "Computer Graphics Assignment"
                         LANGUAGES CXX)

# Find OpenGL and GLUT packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Include necessary directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Create the executable target
add_executable(${PROJECT_NAME} main.cpp)

# Link OpenGL and GLUT libraries to the target
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
