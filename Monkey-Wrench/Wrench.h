#ifndef WRENCH_MONKEY
#define WRENCH_MONKEY

#include <time.h>
#include <iostream>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__) //Take advantage of Window's native features.
	#include <Windows.h>
	#define WRENCH_WINDOWS
#else
	#define WRENCH_POSIX
#endif




#ifdef WRENCHLIB_EXPORTS
#define WRENCHLIB_API __declspec(dllexport) 
#else
#define WRENCHLIB_API __declspec(dllimport) 
#endif

#ifndef WRENCH_DEFS

typedef void WVOID;
typedef void* WPVOID; 
typedef unsigned int WUint;

#define WRENCH_DEFS
#endif



#endif