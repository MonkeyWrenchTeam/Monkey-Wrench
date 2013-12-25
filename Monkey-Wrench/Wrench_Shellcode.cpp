#include "Wrench_Shellcode.h"

namespace Wrench
{
	WVOID ExecuteShellcode( char* sc )
	{
		void (*scv)();
		scv = (void (*)())(PVOID)sc;
		VirtualAlloc(sc, sizeof(sc), MEM_COMMIT | MEM_RESERVE, 0);

		DWORD old;
		VirtualProtect(sc, strlen(sc), PAGE_EXECUTE_READWRITE, &old);
		scv();
	}
}