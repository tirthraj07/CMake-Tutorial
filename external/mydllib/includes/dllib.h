#ifndef DLLIB_H
#define DLLIB_H
#pragma once

#ifdef _WIN32
#ifdef MYDLLIB_EXPORTS
#define DLLIB_API __declspec(dllexport)
#else
#define DLLIB_API __declspec(dllimport)
#endif
#else
#define DLLIB_API
#endif

/*
__declspec(dllexport) tells the linker that you want this object to be made available for other DLL's to import. It is used when creating a DLL that others can link to.

__declspec(dllimport) imports the implementation from a DLL so your application can use it.
*/

// https://stackoverflow.com/questions/3950509/build-succeeded-but-no-lib-file-gets-created
// https://stackoverflow.com/questions/57999/what-is-the-difference-between-dllexport-and-dllimport
// https://stackoverflow.com/questions/2284610/what-is-declspec-and-when-do-i-need-to-use-it
// https://stackoverflow.com/questions/913691/dll-and-lib-files-what-and-why

DLLIB_API void dynamicLibFunction();

#endif