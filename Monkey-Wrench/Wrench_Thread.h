#ifndef WRENCH_THREAD
#define WRENCH_THREAD

#include "Wrench.h"

#ifdef WRENCH_WINDOWS
    #include <process.h>
#else
    #include <pthread.h>
#endif

#define TFUNC(x) (WUint (__stdcall*)(WPVOID))(x)

namespace Wrench
{

#ifdef WRENCH_WINDOWS
 struct WRENCHLIB_API WThread
{
	WUint ThreadID;
	WPVOID ThreadHandle;
};
#else
struct WThread
{
    WThread() {};
    WUint ThreadID;
    pthread_t ThreadHandle;
};
#endif


#ifdef WRENCH_WINDOWS
WRENCHLIB_API WThread MakeThread(WPVOID Function);
WRENCHLIB_API WThread MakeThread( WPVOID Function, WPVOID args );
#else
WRENCHLIB_API WThread MakeThread(void* func);
WRENCHLIB_API WThread MakeThread(void* func, WPVOID args);
#endif



}

#endif
