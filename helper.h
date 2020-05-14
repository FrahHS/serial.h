#ifndef _SHELPER_
#define _SHELPER_
#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef __WIN32__ 
#define _WIN32 1
#endif //__WIN32__

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32

#pragma warning(disable : 4996) //disable errors for unsafe functions

#define INCORRECT -1
#define READ GENERIC_READ 
#define WRITE GENERIC_WRITE 
#ifdef _WIN32

std::wstring towstring(const std::string& str) {    //standard c++ string to wstring converter
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

#endif //_WIN32
#endif //_SHELPER_


