#include "Wrench_Thread.h"

namespace Wrench
{
	
WThread MakeThread( WPVOID Function )
{
	Wrench::WThread nt;
	
	#ifdef WRENCH_WINDOWS
        nt.ThreadHandle = (WPVOID) _beginthreadex(NULL, sizeof(Function), TFUNC(Function), NULL, NULL, &nt.ThreadID);
	#else
	nt.ThreadID = pthread_create(&nt.ThreadHandle, NULL, (WPVOID(*)(WPVOID))func, NULL);
	#endif
	
	return nt;
}

WThread MakeThread( WPVOID Function, WPVOID args )
{
	Wrench::WThread nt;
	
	#ifdef WRENCH_WINDOWS
        nt.ThreadHandle = (WPVOID) _beginthreadex(NULL, sizeof(Function), TFUNC(Function), args, NULL, &nt.ThreadID);
	#else
	nt.ThreadID = pthread_create(&nt.ThreadHandle, NULL, (WPVOID*(*)(WPVOID))func, args);
	#endif
	
	return nt;
}

}
