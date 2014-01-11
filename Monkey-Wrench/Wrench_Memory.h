#ifndef WRENCH_MEMORY
#define WRENCH_MEMORY

#include "Wrench.h"
#include "Wrench_Thread.h"
#include "Wrench_Timer.h"

#ifdef WRENCH_WINDOWS
    #include <Windows.h>
#else
    #include <sys/ptrace.h>
#endif

//Remote memory modification.
namespace Wrench
{
    #ifdef WRENCH_WINDOWS
	WRENCHLIB_API int ModifyMemory(char* Window, unsigned long Pointer, WPVOID Val);
	WRENCHLIB_API WThread FreezeMemory(char* Window, unsigned long Pointer);
	#else
    WRENCHLIB_API int ModifyMemory(pid_t Window, WPVOID Pointer, WPVOID Val);
	WRENCHLIB_API WThread FreezeMemory(pid_t Window, WPVOID Pointer);
	#endif
}

//Smart Pointers

namespace Wrench
{
	template<class T>
	class mem_sPointer
	{
	public:
		inline mem_sPointer()	{
			vol = false;
			lifet = false;
			bLocked = false;
			bmem = NULL;
			emptied = true;
		};

		inline mem_sPointer(T* mem)	{
			vol = false;
			lifet = false;
			bLocked = false;
			bmem = mem;
			emptied = false;
			referenced = true;
		}
		inline ~mem_sPointer() 
		{
			if(!emptied && !referenced) 
			{
				if(sized)
					delete[] bmem;

				if(!sized)
					delete bmem;

				emptied = true;
			}
			else if(!emptied && referenced)
			{
				bmem = NULL;
				emptied = true;
			}
		}

		inline void Erase() 
		{
			if(!emptied && !referenced) 
			{
				if(sized)
					delete[] bmem;

				if(!sized)
					delete bmem;

				emptied = true;
			}
			else if(!emptied && referenced)
			{
				bmem = NULL;
				emptied = true;
			}
		}
		inline void Save(T* mem, int size) 
		{
			if(!bLocked) 
			{
				emptied = false;
				referenced = false;
				bmem = new T[size];
				memcpy(bmem, mem, sizeof(mem));
				sized = true;
			}
		}

		inline void Save(T* mem) 
		{
			if(!bLocked) 
			{
				emptied = false;
				referenced = false;
				bmem = new T[sizeof(mem) + 1];
				memcpy(bmem, mem, sizeof(mem));
				sized = false;
			}
		}
		inline void Lock() {bLocked = true;}
		inline void Unlock() {bLocked = false;}
		inline bool Locked() {return bLocked;}
		inline void SetLifetime(int life)	{
			WClock c;
			lifet = c.GetTimeMilliseconds() + life;
			vol = true;
		}
		inline mem_sPointer& operator= (T mem) {bmem = mem;}

		template<typename C>
		inline C Get()	
		{
			WClock c;
			if((lifet > c.GetTimeMilliseconds()) || (vol == false) )
			{
				return reinterpret_cast<C>(bmem);
			}
			else
			{
				bmem = NULL;
				return NULL;
			}
		}
		//inline bool Compare(mem_sPointer second) {return bmem == second.Get<void*>();}
		//inline bool Compare(mem_sPointer first, mem_sPointer second) {return first.Get<void*>() == second.Get<void*>();}
		//inline bool Compare(void* first, mem_sPointer second) {return first == second.Get<void*>();}
		//inline bool Compare(mem_sPointer first, void* second) {return first.Get<void*>() == second;}

	private:
		int lifet;
		T* bmem;
		bool bLocked;
		bool vol;
		bool emptied;
		bool referenced;
		bool sized;
	};
}
#endif
