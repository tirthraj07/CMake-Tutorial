import platform
import ctypes
import time
import sys

ITERATIONS = 100000
LINUX_PATH = "/mnt/c/Users/LENOVO/Desktop/CMake/bin/libmylib.so"
WINDOWS_PATH = "C:/Users/LENOVO/Desktop/CMake/bin/mylib.dll"
if platform.uname()[0] == "Windows":
    dllname = WINDOWS_PATH
else:
    dllname = LINUX_PATH

mylib = ctypes.CDLL(dllname)

def run_cpp_shared_function():
    mylib.print_nums(ITERATIONS)

def run_python_function():
    for i in range(0, ITERATIONS):
        print("i = ", i)

if __name__ == '__main__':
    n = len(sys.argv)
    runScript = "py"
    if(sys.argv[1] == "cpp"):
        runScript = "cpp"
    else:
        runScript = "py"
    
    start_time = time.time()
    
    if runScript == "cpp":
        run_cpp_shared_function()
    else:
        run_python_function()

    end_time = time.time()
    execution_time = end_time - start_time
    print(f"Type of Script : {runScript}")
    print(f"The function took {execution_time:.5f} seconds to execute.")