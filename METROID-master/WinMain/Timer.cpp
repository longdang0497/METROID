#include "Timer.h"

Timer::Timer()
{
	totalTime = 0;
	elapsedTime = 0;
	LARGE_INTEGER i;

	//Get the frequency from counter. The frequency cannot change while the system is running. 
	//Do this once.
	QueryPerformanceFrequency(&i);

	//Return the number of ticks per second.
	freq_per_secs = (float)(i.QuadPart);

	//Get the current value of the counter.
	QueryPerformanceCounter(&i);
	start = i.QuadPart;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	LARGE_INTEGER i;

	QueryPerformanceCounter(&i);
	elapsedTime = (float)(i.QuadPart - start) / freq_per_secs;

	start = i.QuadPart; // Reset start
	totalTime += elapsedTime;
}
