# Adding External Libraries with Git Submodules

## Tutorial

### Project Structure

```
root
├── external    # Folder for external files
├── main.cpp       # Main executable file
└── CMakeLists.txt
```

### Step 1: Add the external library as a Git submodule
For example
```bash
git submodule add https://github.com/nlohmann/json.git external/json
```
This command will clone the library into the external/json directory of your project.

### Step 2: After adding the submodule, you need to initialize and update it:

```bash
git submodule update --init --recursive
```

### Step 3: Commit the submodule addition:

```bash
git commit -am "Add nlohmann/json as a submodule"
```

### Step 4: Modify Your CMakeLists.txt to Include the Library

```cmake
cmake_minimum_required(VERSION 3.14)
project(MyProject)

add_subdirectory(external/json)
add_executable(MyExecutable main.cpp)
target_link_libraries(MyExecutable PRIVATE nlohmann_json::nlohmann_json)
```

For glfw, do the following
```bash
git submodules add https://github.com/glfw/glfw external/glfw
git submodules update --init --recursive
```

`CMakeLists.txt` looks like this:
```cmake
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
```

The target name (e.g., `nlohmann_json::nlohmann_json` or `glfw`) is defined by the CMake configuration of the library itself. When you add a library as a Git submodule or through add_subdirectory, CMake makes the target available based on the library’s CMakeLists file.

Here’s how to find the target name:

__1. Checking the Library’s Documentation or CMakeLists File__
For most well-documented libraries, the target name is mentioned in the library’s documentation or README. For example:

The nlohmann/json library uses the target name nlohmann_json::nlohmann_json.
The glfw library typically defines a target named glfw.

__2. Inspecting the Library’s CMakeLists.txt__
Inside the library’s CMakeLists.txt file, look for add_library or add_executable commands, as they define the target names. Often, the targets are namespaced to avoid conflicts, such as glfw for GLFW or nlohmann_json::nlohmann_json for nlohmann/json.

For example, in GLFW’s CMakeLists.txt, you would typically see something like this:

```cmake
add_library(glfw ...)
```
This means the target name glfw is used when linking.



## Important Note

Difference between

- __`target_include_directories()`__
__Purpose__: Specifies directories where the compiler can find header files for a given target.
__Usage__: This command is used to add include paths for a specific target (e.g., an executable or library) to find header files.
__Example__:
```cmake
target_include_directories(MyExecutable PRIVATE external/mylib/include)
```
__When to Use__: Use target_include_directories when you have a library or source files with headers that are not in the default include path, and you need to expose these to the target. The PRIVATE, PUBLIC, or INTERFACE keyword determines whether these directories are exposed to other targets that link to this one.

- __`target_link_directories()`__
__Purpose__: Specifies directories where the linker can find libraries (e.g., .lib or .so files) for a target.
__Usage__: This command adds library search paths at link time for a target.
__Example__:
```cmake
target_link_directories(MyExecutable PRIVATE /path/to/library)
```
__When to Use__: target_link_directories is rarely needed when working with libraries managed by CMake (such as libraries added through add_subdirectory or find_package) because those targets usually provide the full path to the library. It’s mostly useful when linking libraries outside of CMake, where only the directory path is specified, and then target_link_libraries is used to link the actual library files.

- __`target_link_libraries()`__
__Purpose__: Links a target with libraries it depends on.
__Usage__: This command specifies which libraries to link against for a given target.
__Example__:
```cmake
target_link_libraries(MyExecutable PRIVATE mylib anotherlib)
```
__When to Use__: Use target_link_libraries to specify dependencies for executables or libraries. This command not only links the target with the libraries but also propagates include paths and compile options associated with the libraries. Libraries specified here must be either targets created by CMake (add_library(mylib ...)) or libraries found with find_package.

- __`add_subdirectory()`__
__Purpose__: Adds a subdirectory containing a CMakeLists.txt file to the current project.
__Usage__: This command is used to include another CMake project or part of a project as a subcomponent of the current project.
__Example__:
```cmake
add_subdirectory(external/glfw)
```
__When to Use__: Use add_subdirectory when you want to include an external library or module that has its own CMake build system. This makes the targets defined in that subdirectory (such as glfw) available in your main project, so you can link against them with target_link_libraries.
