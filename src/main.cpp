#include <iostream>
#include "staticlib.h"
#include "dllib.h"
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    staticLibFunction();
    dynamicLibFunction();
}