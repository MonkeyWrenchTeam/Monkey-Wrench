#ifndef WRENCH_MEMORY
#define WRENCH_MEMORY

#include "Wrench.h"
#include "Wrench_Thread.h"

#include <Windows.h>

namespace Wrench
{
<<<<<<< HEAD
=======

>>>>>>> e10d26ca19f6ee167812467e1f4df696cff2de04
	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, WPVOID Val);
	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, int Val);
	WRENCHLIB_API WThread FreezeMemory(char* Window, unsigned long Pointer);
}

#endif
