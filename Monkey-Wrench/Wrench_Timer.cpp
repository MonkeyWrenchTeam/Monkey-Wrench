#include "Wrench_Timer.h"
#include "Wrench_Manipulation.h"
#ifdef WRENCH_POSIX
#include <string.h>
#endif

namespace Wrench
{
WClock::WClock()
{
	Year = Day = Hours = Minutes = Seconds = 0; //Prevent errors when pulling the time.
	#ifdef WRENCH_WINDOWS
	Month = "";
	#else
	Month = 0;
	#endif
}

int WClock::GetTimeHours()
{
	PullTime();
	return (int)(Hours + (Minutes / 60) + ((Seconds / 60) / 60));
}

int WClock::GetTimeMilliseconds()
{
	PullTime();
	return (int)(((Hours * 60) * 60) * 1000) + ((Minutes * 60) * 1000) + (Seconds * 1000);
}

int WClock::GetTimeMinutes()
{
	PullTime();
	return (int)(Hours * 60) + Minutes + (Seconds / 60);
}

int WClock::GetTimeSeconds()
{
	PullTime();
	return (int)((Hours * 60) * 60) + (Minutes * 60) + Seconds;
}

int WClock::GetDay()
{
	PullTime();
	return Day;
}

#ifdef WRENCH_WINDOWS
char* WClock::GetMonth()
{
	PullTime();
	return Month;
}
#else
int WClock::GetMonth()
{
	PullTime();
	return Month;
}
#endif

int WClock::GetYear()
{
	PullTime();
	return Year;
}

void WClock::PullTime()
{
	#ifdef WRENCH_POSIX
	_time = time(NULL);
	struct tm tm = *localtime(&_time);
	Year = tm.tm_year + 1900;
	Month = tm.tm_mon + 1;
	Day = tm.tm_mday;
	Hours = tm.tm_hour;
	Minutes = tm.tm_min;
	Seconds = tm.tm_sec;
	#endif

	#ifdef WRENCH_WINDOWS
	char* nCount = ctime(&_time);

	char* vars[7];

	int i = 0;
	char * pch = strtok(nCount," :");
	while ( pch != NULL)
	{
		vars[i] = pch;
		++i;
		pch = strtok(NULL," :");
	}
	Month = vars[1];
	Day = StringToInt(vars[2]);
	Hours = StringToInt(vars[3]);
	Minutes = StringToInt(vars[4]);
	Seconds = StringToInt(vars[5]);
	Year = StringToInt(vars[6]);
	#else

	#endif
}
}
