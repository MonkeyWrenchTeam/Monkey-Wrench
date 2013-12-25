#include "Wrench_Thread.h"

namespace Wrench
{

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

}