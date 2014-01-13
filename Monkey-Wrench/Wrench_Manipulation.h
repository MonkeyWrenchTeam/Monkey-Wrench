#ifndef WRENCH_MANIPULATION
#define WRENCH_MANIPULATION
#include "Wrench.h"
#include <map>
#include <string>
#include <sstream>

namespace Wrench
{
    //Simple conversion
	WRENCHLIB_API std::string IntToString(int t);
	WRENCHLIB_API int StringToInt(std::string t);
	WRENCHLIB_API int StringToInt(const char* t);
	WRENCHLIB_API int StringToInt(char* t);

	//String manipulation
	WRENCHLIB_API std::string str_merge( int num, ... );
	WRENCHLIB_API std::string str_tolower(char* t);
	WRENCHLIB_API std::string str_toupper(char* t);
}

#endif
