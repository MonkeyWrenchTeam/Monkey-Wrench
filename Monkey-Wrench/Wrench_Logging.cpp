#include "Wrench_Logging.h"

#define col_br 0x0C
#define col_bg 0x0A
#define col_bb 0x0B
#define col_def 0x07

namespace Wrench
{
	void Print( char* message )
	{
		std::cout << message;
	}

	void Print( char* message, WORD color )
	{
		HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute( han, color );
		std::cout << message;
		SetConsoleTextAttribute( han, col_def);
	}

	void Print( char* message, WORD foreground, WORD background )
	{
		HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute( han, foreground + background);
			std::cout << message;
		SetConsoleTextAttribute( han, col_def);
	}

	void Printfile( char* message, bool truncate, char* path )
	{

	}
}