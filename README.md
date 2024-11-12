### CMAKE Introduction

> Refer: https://cliutils.gitlab.io/modern-cmake/chapters/intro/running.html

---

CMake works by reading a file called CMakeLists.txt, where you specify:

- Project details (like name and version)
- Source files to compile
- Compiler options
- Libraries to link, if any

```bash
cmake [options] -S <path-to-source> -B <path-to-build>
```

---

## Do's and Don'ts

### CMake Antipatterns
- __Do not use global functions__: This includes link_directories, include_libraries, and similar.

- __Don’t add unneeded PUBLIC requirements__: You should avoid forcing something on users that is not required (-Wall). Make these PRIVATE instead.

- __Don’t GLOB files__: Make or another tool will not know if you add files without rerunning CMake. Note that CMake 3.12 adds a CONFIGURE_DEPENDS flag that makes this far better if you need to use it.

- __Link to built files directly__: Always link to targets if available.

- __Never skip PUBLIC/PRIVATE when linking__: This causes all future linking to be keyword-less.

## CMake Patterns
- __Treat CMake as code__: It is code. It should be as clean and readable as all other code.

- __Think in targets__: Your targets should represent concepts. Make an (IMPORTED) INTERFACE target for anything that should stay together and link to that.
 
- __Export your interface__: You should be able to run from build or install.

- __Write a Config.cmake file__: This is what a library author should do to support clients.

- __Make ALIAS targets to keep usage consistent__: Using add_subdirectory and find_package should provide the same targets and namespaces.

- __Combine common functionality into clearly documented functions or macros__: Functions are better usually.

- __Use lowercase function names__: CMake functions and macros can be called lower or upper case. Always use lower case. Upper case is for variables.

- __Use cmake_policy and/or range of versions__: Policies change for a reason. Only piecemeal set OLD policies if you have to.


---

## Tutorial

### Step 1: Start by creating `CMakeLists.txt` and a `build` folder

Unless otherwise noted, you should always make a build directory and build from there. You can technically do an in-source build, but you’ll have to be careful not to overwrite files or add them to git, so just don’t.

```bash
touch CMakeLists.txt
mkdir build
```

### Step 2: Run the CMake command by specifying the source and build folder path
Note: Empty `CMakeLists.txt` works fine

```bash
cmake -S . -B build/
```

You should see something like this
```bash
CMake Warning (dev) in CMakeLists.txt:
  No project() command is present.  The top-level CMakeLists.txt file must
  contain a literal, direct call to the project() command.  Add a line of
  code such as

    project(ProjectName)

  near the top of the file, but after cmake_minimum_required().

  CMake is pretending there is a "project(Project)" command on the first
  line.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/c/Users/LENOVO/Desktop/CMake/build
```


It should generate the following files
```
- CMakeCache.txt  
- CMakeFiles  
- Makefile  
- cmake_install.cmake
```

---

### Step 3: Configuring CMakeLists.txt

#### 3.1 cmake_minimum_required()
Here’s the first line of every CMakeLists.txt, which is the required name of the file CMake looks for:
```cmake
cmake_minimum_required(VERSION 3.15)
```
Let’s mention a bit of CMake syntax. The command name cmake_minimum_required is case insensitive, so the common practice is to use lower case
The VERSION is a special keyword for this function. And the value of the version follows the keyword.


Starting in CMake 3.12, this supports a range, such as VERSION 3.15...3.31; this means you support as low as 3.15 but have also tested it with the new policy settings up to 3.31.
```cmake
cmake_minimum_required(VERSION 3.15...3.31)
```

#### 3.2 project
Now, every top-level CMake file will have the next line:

```cmake
project(MyProject VERSION 1.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)
```

Now we see even more syntax. 
Strings are quoted, whitespace doesn’t matter, and the __name of the project is the first argument__ (positional). 

__All the keyword arguments here are optional__. 

- The version sets a bunch of variables, like MyProject_VERSION and PROJECT_VERSION. 
- The languages are C, CXX, Fortran, ASM, CUDA (CMake 3.8+), CSharp (3.8+), and SWIFT (CMake 3.15+ experimental). C CXX is the default. 
- In CMake 3.9, DESCRIPTION was added to set a project description, as well. 

> You can add comments with the # character. CMake does have an inline syntax for comments too, but it’s rarely used.

#### 3.3 Making an executable

```cmake
add_executable(one two.cpp three.h)
```

There are several things to unpack here. 
- `one` is both the __name of the executable file__ generated, and the __name of the CMake target__ created.
- The source file list comes next, and you can list as many as you’d like. CMake is smart, and will __only compile source file extensions__. 
- The headers will be, for most intents and purposes, ignored; the only reason to list them is to get them to show up in IDEs. 


## Example

`main.cpp`
```cpp
#include <iostream>

int main(){
    std::cout<< "Hello from CMake!" << std::endl;
}
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.15)

project(NewCMakeProject VERSION 1.0
                        DESCRIPTION "Very First CMake Project"
                        LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)
```

To Build
```bash
mkdir build
cmake -S . -B build/
```

Output
```bash
cmake -S . -B build/
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/c/Users/LENOVO/Desktop/CMake/build
```

To Compile and Run
```bash
### Build the target
cd build
make

[ 50%] Building CXX object CMakeFiles/NewCMakeProject.dir/main.cpp.o
[100%] Linking CXX executable NewCMakeProject
[100%] Built target NewCMakeProject

### Run the target
./NewCMakeProject
Hello from CMake!
```