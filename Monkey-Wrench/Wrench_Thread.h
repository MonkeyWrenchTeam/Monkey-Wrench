#ifndef WRENCH_THREAD
#define WRENCH_THREAD

#include "Wrench.h"
#include <process.h>

#ifdef WIN32
#include <process.h>
#endif

#define TFUNC(x) (WUint (__stdcall*)(WPVOID))(x)

namespace Wrench
{

 struct WRENCHLIB_API WThread
{
	WUint ThreadID;
	WPVOID ThreadHandle;
};

WRENCHLIB_API WThread MakeThread(WPVOID Function);
WRENCHLIB_API WThread MakeThread( WPVOID Function, WPVOID args );

}

#endif