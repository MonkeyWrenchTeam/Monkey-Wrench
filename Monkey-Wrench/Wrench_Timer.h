#ifndef WRENCH_TIME
#define WRENCH_TIME

#include "Wrench.h"

namespace Wrench{

class WRENCHLIB_API WClock
{
public:
	WClock();
	 int GetTimeMilliseconds();
	 int GetTimeSeconds();
	 int GetTimeMinutes();
	 int GetTimeHours();
	 int GetDay();
	 int GetYear();
	 void PullTime();
        int GetMonth();
    

private:
	time_t _time;

    //In the Windows version, the month is represented as the name of the month.
    //However, using POSIX, localtime gives the number of the month (1-12)
    
        int Month;
	
	int Year;
	int Seconds;
	int Minutes;
	int Hours;
	int MS;
	int Day;
};

}

#endif
