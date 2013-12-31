#ifndef WRENCH_LOGGING
#define WRENCH_LOGGING

#ifdef WRENCH_WINDOWS
#include <Windows.h>
#endif

#include "Wrench.h"

#ifdef WRENCH_WINDOWS
    #define COL WORD
#else
    #define COL char*
#endif

namespace Wrench
{
	enum WRENCH_PLACEMENT{
		PLACEMENT_SUFFIX,
		PLACEMENT_PREFIX,
		PLACEMENT_PREFIX_AND_SUFFIX
	};
	WRENCHLIB_API void Print(char* message); //Standard;
	WRENCHLIB_API void Print(char* message, COL color);
    WRENCHLIB_API void Print(char* message, COL foreground, COL background);
	WRENCHLIB_API void Printfile(char* message, bool truncate, char* path);
	WRENCHLIB_API void Printfile(char* message, int placement, char* ix, bool truncate, char* path);
	WRENCHLIB_API void Printfile(char* message, char* prefix, char* suffix, bool truncate, char* path);
}

#endif
