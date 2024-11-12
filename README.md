# Making a Library

Let's say you want to create a library called `mylib` and use it in a project. We’ll create a simple setup where `mylib` provides a function, and we’ll use it in our main application.


### Project Structure
```
root/
├── CMakeLists.txt        # Main CMake file
├── main.cpp              # Main application
└── lib/
    ├── CMakeLists.txt 
    └── mylib/
        ├── CMakeLists.txt    # CMake file for the library
        ├── mylib.h           # Library header
        └── mylib.cpp         # Library implementation
```

### Tutorial

#### Step 1: Create `mylib.h` and `mylib.cpp` 
Create the header and source file for your library and give it some functionality

For example
`mylib.h` contains some math functions as follows:

```cpp
#pragma once

namespace mylib {
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);
}
```

#### Step 2: Create a `CMakeLists.txt` in the library
  
```bash
cd lib/mylib
touch CMakeLists.txt
```
  
#### Step 3: Use add_library to create a library target
Making a library is done with add_library, and is just about as simple:

```cmake
add_library(one STATIC two.cpp three.h)
```

You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of BUILD_SHARED_LIBS will be used to pick between STATIC and SHARED.

__What is a Library?__  
A library is a collection of code (functions, classes, etc.) that you can reuse in multiple programs. Libraries let you write code once and use it anywhere, making it easier to organize and reuse functionality. Libraries come in two main forms:

- __Static Libraries (.lib or .a files)__: These are bundled with the executable at compile time, so the code from the library becomes part of the executable file.
- __Shared or Dynamic Libraries (.dll or .so files)__: These are separate files loaded at runtime, allowing multiple programs to share the same library code without duplicating it

In this example, we’re creating a library named mylib

__What does add_library() do?__  
In CMake, the add_library command is used to define a new __library target__. 
A __target__ in CMake is a __named collection of source files and settings__, such as compile options or linked libraries. By adding a library target, you’re telling CMake to compile certain files into a library that other parts of your project can use.
  
  
```cmake
add_library(mylib mylib.cpp)
```

- Creates a library target called mylib.
- Specifies mylib.cpp as the source file to compile into this library.

When CMake processes this line, it knows to compile mylib.cpp and generate a library file (like libmylib.a or libmylib.so on Linux, or mylib.lib on Windows). This library can then be linked to other parts of the project.


#### Step 4: use `target_include_directories` function

Now we’ve specified a target, how do we add information about it? For example, maybe it needs an include directory:

```cmake
target_include_directories(one PUBLIC include)
```

When we create a library in C++, it usually has two parts:

- __Header Files (.h or .hpp)__: These define the functions, classes, and interfaces.
- __Source Files (.cpp)__: These contain the actual implementation of the functions declared in the header files

To allow other files (such as main.cpp in our example) to use the functions in mylib, they need to know about the declarations in the header file (mylib.h). For this to happen, C++ needs to find the directory where the header file is located.

That’s where target_include_directories comes in:

```cmake
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

__target_include_directories__ specifies directories to be searched for header files when #include is used.

__mylib__ is the target we’re adding include directories to.

__PUBLIC__ means that any project that links to mylib will also inherit this include path.

__${CMAKE_CURRENT_SOURCE_DIR}__ expands to the current directory (lib/mylib), where mylib.h is located. This makes mylib.h accessible to files that include mylib.

So finally our `/lib/mylib/CMakeLists.txt` looks like follows
```cmake
cmake_minimum_required(VERSION 3.15)

project(mylib VERSION 1.0
              DESCRIPTION "Simple Library that adds math functions"  
              LANGUAGES CXX)

add_library(mylib mylib.cpp)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

#### Step 5: Include the `mylib` folder as a sub directory in `lib` folder

Inside `/lib/CMakeLists.txt`,  import the mylib library

```cmake
add_subdirectory(mylib)
```

__add_subdirectory(mylib)__ tells CMake to process the CMakeLists.txt file inside the mylib directory.

#### Step 6: Configure the Root CMakeLists.txt file

This is the main CMake file that configures the overall project, defining the main executable and linking everything together.

```cmake
cmake_minimum_required(VERSION 3.15)

project(MyProject VERSION 1.0
                  DESCRIPTION "Project that showcases Static libraries in C++"
                  LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)
```

The above was explained in the previous Tutorial, so skipping that part

```cmake
add_subdirectory(lib)
```

__add_subdirectory(lib)__ tells CMake to process the CMakeLists.txt in the lib folder.
This brings in any targets defined inside lib, including the mylib library.

```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE mylib)
```

- __target_link_libraries__ links libraries to a target.
- MyProject is the target (executable) that we’re linking libraries to.
- __PRIVATE__ means that MyProject will link to mylib, but any other target linking to MyProject won’t automatically link to mylib
- mylib is the library we want to link, making its functions available to main.cpp


```cmake
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
```
This is the CMake command to add one or more include paths (directories with header files) to a target.
Without this command, main.cpp would not know where to look for mylib/mylib.h. By default, the compiler only looks for headers in certain system directories or in directories you explicitly tell it about.

So when #include "mylib/mylib.h" appears in main.cpp:

The compiler needs to know where to find this file.
By adding __${CMAKE_SOURCE_DIR}/lib__ as an include path, the compiler can locate __mylib/mylib.h__ in lib/mylib

The compiler, when processing main.cpp, will search through the include paths in the order they are given.
Since lib is added to the include paths, the compiler can now locate mylib/mylib.h under lib.

#### Step 7: Make and Run

```bash
mkdir build
cd build
cmake ..

# -------- OUTPUT -------- 
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/c/Users/LENOVO/Desktop/CMake/build

# -------- END -------- 

make

#  -------- OUTPUT -------- 
[ 25%] Building CXX object lib/mylib/CMakeFiles/mylib.dir/mylib.cpp.o
[ 50%] Linking CXX static library libmylib.a
[ 50%] Built target mylib
[ 75%] Building CXX object CMakeFiles/MyProject.dir/main.cpp.o
[100%] Linking CXX executable MyProject
[100%] Built target MyProject
# -------- END -------- 

./MyProject

#  -------- OUTPUT -------- 
10 + 20 = 30
10 - 20 = -10
10 * 20 = 200
20 / 10 = 2
# -------- END -------- 

```