#ifndef WRENCH_SHELLCODE
#define WRENCH_SHELLCODE

#include "Wrench.h"

namespace Wrench
{
#ifdef WRENCH_WINDOWS
	WRENCHLIB_API WVOID ExecuteShellcode(char* sc);
#endif
}

#endif
