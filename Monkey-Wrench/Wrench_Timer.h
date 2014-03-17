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
