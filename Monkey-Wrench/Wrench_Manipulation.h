#ifndef WRENCH_MANIPULATION
#define WRENCH_MANIPULATION
#include "Wrench.h"
#include <map>
#include <string>
#include <sstream>

namespace Wrench
{
    //Simple conversion
    WRENCHLIB_API int StringToInt(char* t);
    WRENCHLIB_API std::string IntToString(int t);
}

#endif
