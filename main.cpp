#include <iostream>
#include "mylib/mylib.h"


int main(){
    std::cout << "10 + 20 = " << mylib::add(10,20) << std::endl;
    std::cout << "10 - 20 = " << mylib::sub(10,20) << std::endl;
    std::cout << "10 * 20 = " << mylib::mul(10,20) << std::endl;
    std::cout << "20 / 10 = " << mylib::div(20,10) << std::endl;
}