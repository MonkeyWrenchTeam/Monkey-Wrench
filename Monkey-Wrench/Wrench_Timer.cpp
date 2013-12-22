#include "Wrench_Timer.h"

namespace Wrench
{

WClock::WClock()
{
	Year = Day = Hours = Minutes = Seconds = 0; //Prevent errors when pulling the time.
	Month = "";
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

char* WClock::GetMonth()
{
	PullTime();
	return Month;
}

int WClock::GetYear()
{
	PullTime();
	return Year;
}

void WClock::PullTime()
{
	_time = time(NULL);
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
	Day = atoi(vars[2]);
	Hours = atoi(vars[3]);
	Minutes = atoi(vars[4]);
	Seconds = atoi(vars[5]);
	Year = atoi(vars[6]);

}

}