#ifndef WRENCH_LOGGING
#define WRENCH_LOGGING

#include <Windows.h>
#include "Wrench.h"

namespace Wrench
{
	enum WRENCH_PLACEMENT{
		PLACEMENT_SUFFIX,
		PLACEMENT_PREFIX,
		PLACEMENT_PREFIX_AND_SUFFIX
	};
	WRENCHLIB_API void Print(char* message); //Standard;
	WRENCHLIB_API void Print(char* message, WORD color);
	WRENCHLIB_API void Print(char* message, WORD foreground, WORD background);
	WRENCHLIB_API void Printfile(char* message, bool truncate, char* path);
	WRENCHLIB_API void Printfile(char* message, int placement, char* ix, bool truncate, char* path);
	WRENCHLIB_API void Printfile(char* message, char* prefix, char* suffix, bool truncate, char* path);
}

#endif