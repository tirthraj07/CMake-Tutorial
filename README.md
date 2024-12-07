# C++ Shared Libraries with Python using CTypes

`ctypes` is a foreign function library for Python. It provides C compatible data types, and allows calling functions in DLLs or shared libraries. It can be used to wrap these libraries in pure Python.



## Build Instructions

Step 1: Compile Shared C++ Library
```bash
cd mylib
mkdir build
cd build
cmake ..
make
```

Step 2: Copy the Shared Library (.dll for Windows) to `bin` folder in root

Step 3: Run Python Script

```bash
python main.py
```
