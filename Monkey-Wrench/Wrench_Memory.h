#ifndef WRENCH_MEMORY
#define WRENCH_MEMORY

#include "Wrench.h"
#include "Wrench_Thread.h"

#include <Windows.h>

namespace Wrench
{
	struct WRENCHLIB_API WSMem
	{
		char* type;
		void* mem;
	};
	WRENCHLIB_API WSMem* FormatMemory(void* memory, char* type);

	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, WPVOID Val);
	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, int Val);
	WRENCHLIB_API WThread FreezeMemory(char* Window, unsigned long Pointer);
}

#endif