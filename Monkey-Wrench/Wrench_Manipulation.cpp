#include "Wrench_Manipulation.h"
#include <map>
#include <string>
#include <sstream>

#ifdef WRENCH_POSIX
    #include <cstring>
    #include <math.h>
#endif

namespace Wrench
{

std::string IntToString(int t)
{
	std::stringstream ss;
	ss << t;
	std::string buf = ss.str();
	return buf;
}

std::string str_merge( int num, ... )
{
	std::stringstream ss;
	char* val;
	va_list vl;
	va_start(vl, num);
	for(int i = 0; i <= num - 1; ++i)
	{
		val = va_arg(vl, char*);

		while((WPVOID)val == 0) //Corrupted char, go no further!
			break;

		ss << val;
	}
	std::string tmp = ss.str();
	return tmp;
}

int StringToInt(std::string t)
{
	std::map<char, int> a;
	for(int i = 48; i <= 57; i++)
	{
		a[i] = (i-48);
	}
	int ln = 0;
	for(int i = 0; i <= strlen(t.c_str()) - 1; ++i)
	{
		ln += pow((long double)10, (int)(strlen(t.c_str()) - 1)- i) * a[t.c_str()[i]];
	}
	a.erase(a.begin(), a.end());
	return ln;
}

int StringToInt(const char* t)
{
	std::map<char, int> a;
	for(int i = 48; i <= 57; i++)
	{
		a[i] = (i-48);
	}
	int ln = 0;
	for(int i = 0; i <= strlen(t) - 1; ++i)
	{
		ln += pow((long double)10, (int)(strlen(t) - 1)- i) * a[t[i]];
	}
	a.erase(a.begin(), a.end());
	return ln;
}

int StringToInt(char* t)
{
	std::map<char, int> a;
	for(int i = 48; i <= 57; i++)
	{
		a[i] = (i-48);
	}
	int ln = 0;
	for(int i = 0; i <= strlen(t) - 1; ++i)
	{
		ln += pow((long double)10, (int)(strlen(t) - 1)- i) * a[t[i]];
	}
	a.erase(a.begin(), a.end());
	return ln;
}

std::string str_tolower(char* t)
{
	std::string b = t;
	for(int i = 0; i <= strlen(b.c_str()) - 1; ++i)
	{
		if(t[i] >= 65 && t[i] <= 90)
		{
			b[i] = t[i] + 32;
		}
		else
		{
			b[i] = t[i];
		}
	}

	return b;
}

std::string str_toupper(char* t)
{
	std::string b = t;
	for(int i = 0; i <= strlen(b.c_str()) - 1; ++i)
	{
		if(t[i] >= 97 && t[i] <= 122)
		{
			b[i] = t[i] - 32;
		}
		else
		{
			b[i] = t[i];
		}
	}

	return b;
}


}
