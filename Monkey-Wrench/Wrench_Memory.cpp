#include "Wrench_Memory.h"

namespace Wrench
{
    #ifdef WRENCH_WINDOWS
	int ModifyMemory( char* Window, unsigned long Pointer, WPVOID Val )
	{

		HWND hWnd = FindWindowA(0, Window);
		if(hWnd == 0)
			return 1;// Can't find Window

		DWORD ID;
		GetWindowThreadProcessId(hWnd, &ID);
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ID);
		if(!hProc)
			return 2;// Can't Open the Process

		int ret = WriteProcessMemory(hProc, (LPVOID)Pointer, &Val, (DWORD)sizeof(Val), NULL);
		CloseHandle(hProc);

		if(ret <= 0)
			return 3;// Unable to write the memory

		return 0; //Memory written
	}

	int __FMR(void * _alst[])
	{
		char* W = (char*)_alst[0];
		unsigned long P = (unsigned long)_alst[1];
		WPVOID V = (WPVOID)_alst[2];

		while(true)
		{
			int ret = ModifyMemory(W, P, V);
			if(ret == 1 || ret == 2 || ret == 3) //Any error, can't find window, can't open process or can't write to memory.
				break;
		}
		delete[] _alst;
		return 0;
	}

	WThread FreezeMemory( char* Window, unsigned long Pointer )
	{

		HWND hWnd = FindWindowA(0, Window);

		DWORD ID;
		GetWindowThreadProcessId(hWnd, &ID);
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ID);

		LPVOID Buffer;
		ReadProcessMemory(hProc, (LPVOID)Pointer, &Buffer, sizeof(Buffer), NULL);

		WThread nt;
		WPVOID* arglist = new WPVOID[3];
		arglist [0] = Window;
		arglist [1] = (WPVOID)Pointer;
		arglist [2] = Buffer;

		nt = MakeThread(__FMR, arglist);

		return nt;
	}


	#else

    WRENCHLIB_API int ModifyMemory(pid_t Window, WPVOID Pointer, WPVOID Val)
    {
        return ptrace(PTRACE_POKEDATA, Window, Pointer, Val);
    }

	WRENCHLIB_API WThread FreezeMemory(pid_t Window, WPVOID Pointer)
	{
	}

	#endif
}
