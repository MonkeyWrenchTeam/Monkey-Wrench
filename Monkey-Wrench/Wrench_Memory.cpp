#include "Wrench_Memory.h"

namespace Wrench
{
	VOID ModifyMemory( char* Window, unsigned long Pointer, char* Val )
	{
		HWND hWnd = FindWindowA(0, Window);
		if(hWnd == 0)
		{

			return;// NULL;
		}
		DWORD ID;
		GetWindowThreadProcessId(hWnd, &ID);
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ID);
		if(!hProc)
			return;// NULL;

		int ret = WriteProcessMemory(hProc, (LPVOID)Pointer, &Val, (DWORD)sizeof(Val), NULL);
		CloseHandle(hProc);

		if(ret <= 0)
			return;// NULL;
	}

	VOID ModifyMemory( char* Window, unsigned long Pointer, int Val )
	{
		HWND hWnd = FindWindowA(0, Window);
		if(hWnd == 0)
		{
			
			return;// NULL;
		}
		DWORD ID;
		GetWindowThreadProcessId(hWnd, &ID);
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ID);
		if(!hProc)
			return;// NULL;

		int ret = WriteProcessMemory(hProc, (LPVOID)Pointer, &Val, (DWORD)sizeof(Val), NULL);
		CloseHandle(hProc);

		if(ret <= 0)
			return;// NULL;
	}
}