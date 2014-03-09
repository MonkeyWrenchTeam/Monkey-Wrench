#include "Wrench_Shellcode.h"
#include <Windows.h>

namespace Wrench
{
#ifdef WRENCH_WINDOWS
	WVOID ExecuteShellcode( char* sc )
	{
		void (*scv)();
		scv = (void (*)())(WPVOID)sc;
		VirtualAlloc(sc, sizeof(sc), MEM_COMMIT | MEM_RESERVE, 0);

		DWORD old;
		VirtualProtect(sc, strlen(sc), PAGE_EXECUTE_READWRITE, &old);
		scv();
	}
#endif
}
