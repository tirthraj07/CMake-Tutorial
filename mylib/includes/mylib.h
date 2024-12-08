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
	EXPORT void hello_world();
	EXPORT void print_nums(int num);
}

#endif
