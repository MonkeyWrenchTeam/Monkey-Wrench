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
	 char* GetMonth();
	 void PullTime();

private:
	time_t _time;

	char* Month;
	int Year;
	int Seconds;
	int Minutes;
	int Hours;
	int MS;
	int Day;
};

}

#endif