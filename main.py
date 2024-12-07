import ctypes

mylib = ctypes.CDLL("C:/Users/LENOVO/Desktop/CMake/bin/mylib.dll")
mylib.print_hello_world()
