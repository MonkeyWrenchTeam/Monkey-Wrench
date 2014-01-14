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
	WRENCHLIB_API void Print(WString message); //Standard;
	WRENCHLIB_API void Print(WString message, COL color);
    WRENCHLIB_API void Print(WString message, COL foreground, COL background);
	WRENCHLIB_API void Printfile(WString message, bool truncate, WString path);
	WRENCHLIB_API void Printfile(WString message, int placement, WString ix, bool truncate, WString path);
	WRENCHLIB_API void Printfile(WString message, WString prefix, WString suffix, bool truncate, WString path);
}

#endif
