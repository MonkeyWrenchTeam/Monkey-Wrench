#ifndef WRENCH_LOGGING
#define WRENCH_LOGGING

#include <Windows.h>
#include "Wrench.h"

namespace Wrench
{
	WRENCHLIB_API void Print(char* message); //Standard;
	WRENCHLIB_API void Print(char* message, WORD color);
	WRENCHLIB_API void Print(char* message, WORD foreground, WORD background);
	WRENCHLIB_API void Printfile(char* message, bool truncate, char* path);
}

#endif