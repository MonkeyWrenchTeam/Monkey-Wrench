#include "Wrench_Logging.h"
#include <fstream>

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
		SetConsoleTextAttribute( han, 0x07);
	}

	void Print( char* message, WORD foreground, WORD background )
	{
		HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute( han, foreground + background);
			std::cout << message;
		SetConsoleTextAttribute( han, 0x07);
	}

	void Printfile( char* message, bool truncate, char* path )
	{
		int flags;

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;

		std::ofstream fs(path, flags);
		fs << message << std::endl;
	}

	void Printfile( char* message, int placement, char* ix, bool truncate, char* path )
	{
		int flags;

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;

		std::ofstream fs(path, flags);

		switch(placement)
		{
			case PLACEMENT_PREFIX:
				fs << ix << message << std::endl;
				break;
			case PLACEMENT_SUFFIX:
				fs << message << ix << std::endl;
				break;
		}
		
	}

	void Printfile( char* message, char* prefix, char* suffix, bool truncate, char* path )
	{
		int flags;

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;

		std::ofstream fs(path, flags);
		fs << prefix << message << suffix << std::endl;
	}


}