#include "mylib.h"
#include <iostream>

// POSIX systems: Disable synchronization when the shared library is loaded
#ifdef __linux__
__attribute__((constructor)) void disable_stdio_sync()
{
	std::cin.tie(nullptr);
}
#endif

// Windows systems: Disable synchronization in DllMain
#ifdef _WIN32
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		std::cout << "Windows DLL Loaded" << std::endl;
		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);
	}
	return TRUE;
}
#endif

void hello_world()
{
	std::cout << "Hello World!" << std::endl;
}

void print_nums(int num)
{
	for (int i = 0; i < abs(num); i++)
	{
		std::cout << "i = " << i << std::endl;
	}
}
