#ifndef WRENCH_MONKEY
#define WRENCH_MONKEY

#include <time.h>
#include <iostream>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__) //Take advantage of Window's native features.
	#define WRENCH_WINDOWS
#else
	#define WRENCH_POSIX
#endif




#ifdef WRENCHLIB_EXPORTS
    #ifdef WRENCH_WINDOWS
        #define WRENCHLIB_API __declspec(dllexport)
    #endif
    #ifdef WRENCH_POSIX
        #define WRENCHLIB_API
    #endif
#else

    #ifdef WRENCH_WINDOWS
        #define WRENCHLIB_API __declspec(dllimport)
    #endif

    #ifdef WRENCH_POSIX
        #define WRENCHLIB_API
    #endif
#endif

#ifndef WRENCH_DEFS

typedef void WVOID;
typedef void* WPVOID;
typedef unsigned int WUint;
typedef std::string WString;

#define WRENCH_DEFS
#endif



#endif
