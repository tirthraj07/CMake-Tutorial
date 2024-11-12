#include "mylib.h"
#include <stdexcept>


int mylib::add(int a, int b){
    return a+b;
}

int mylib::sub(int a, int b){
    return a-b;
}

int mylib::mul(int a, int b){
    return a*b;
}

int mylib::div(int a, int b){
    if (b == 0){
        throw std::runtime_error("Division by zero not allowed!");
    }
    return a/b;
}