#include <Wrench.h>
#include <map>
#include <string>
#include <sstream>

#ifdef WRENCH_POSIX
    #include <cstring>
    #include <math.h>
#endif

namespace Wrench
{

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

std::string IntToString(int t)
{
	return dynamic_cast<std::stringstream&>( ( std::stringstream() << t ) ).str();
}


}
