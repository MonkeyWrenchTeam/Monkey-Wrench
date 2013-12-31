#include "Wrench_Thread.h"

namespace Wrench
{
#ifdef WRENCH_WINDOWS
WThread MakeThread( WPVOID Function )
{
	Wrench::WThread nt;
        nt.ThreadHandle = (WPVOID) _beginthreadex(NULL, sizeof(Function), TFUNC(Function), NULL, NULL, &nt.ThreadID);
	return nt;
}

WThread MakeThread( WPVOID Function, WPVOID args )
{
	Wrench::WThread nt;
        nt.ThreadHandle = (WPVOID) _beginthreadex(NULL, sizeof(Function), TFUNC(Function), args, NULL, &nt.ThreadID);
	return nt;
}
#else

WThread MakeThread(void*(*func)(void *))
{
    Wrench::WThread nt;
    nt.ThreadID = pthread_create(&nt.ThreadHandle, NULL, func, NULL);
    return nt;
}

WThread MakeThread( void*(*func)(void *), WPVOID args )
{
    Wrench::WThread nt;
    nt.ThreadID = pthread_create(&nt.ThreadHandle, NULL, func, args);
    return nt;
}
#endif
}
