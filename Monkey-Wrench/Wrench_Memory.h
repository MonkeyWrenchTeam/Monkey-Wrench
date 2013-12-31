#ifndef WRENCH_MEMORY
#define WRENCH_MEMORY

#include "Wrench.h"
#include "Wrench_Thread.h"

#ifdef WRENCH_WINDOWS
    #include <Windows.h>
#else
    #include <sys/ptrace.h>
#endif

namespace Wrench
{
    #ifdef WRENCH_WINDOWS
	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, WPVOID Val);
	WRENCHLIB_API WThread FreezeMemory(char* Window, unsigned long Pointer);
	#else
    WRENCHLIB_API int ModifyMemory(pid_t Window, WPVOID Pointer, WPVOID Val);
	WRENCHLIB_API WThread FreezeMemory(pid_t Window, WPVOID Pointer);
	#endif
}

#endif
