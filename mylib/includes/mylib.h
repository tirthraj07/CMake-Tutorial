#ifndef MYLIB_H
#define MYLIB_H
#pragma once

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C"
{
    EXPORT void print_hello_world();
    EXPORT bool is_even(int num);
}

#endif
