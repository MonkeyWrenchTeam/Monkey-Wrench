#ifndef WRENCH_MEMORY
#define WRENCH_MEMORY

#include "Wrench.h"
#include <Windows.h>

namespace Wrench
{
	WRENCHLIB_API VOID ModifyMemory(char* Window, unsigned long Pointer, char* Val);
	WRENCHLIB_API VOID ModifyMemory(char* Window, unsigned long Pointer, int Val);
	WRENCHLIB_API VOID FreezeMemory(char* Window, unsigned long Pointer);
}

#endif