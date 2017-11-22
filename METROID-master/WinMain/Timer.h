#pragma once
#include <Windows.h>

class Timer
{
private:
	float elapsedTime;
	float totalTime;
	float freq_per_secs;
	LONGLONG start;
public:
	Timer();
	~Timer();

	void Update();
};