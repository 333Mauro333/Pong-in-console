#include "timer.h"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;


namespace pong_in_console
{
	Timer::Timer()
	{
		startTimeReference = 0;
		elapsedTime = 0;
		theTimeBeganToCount = false;
	}
	Timer::~Timer()
	{

	}

	void Timer::startCounting()
	{
		theTimeBeganToCount = true;

		saveStartTimeReference();
	}
	void Timer::updateTime()
	{
		if (theTimeBeganToCount)
		{
			saveElapsedTime();
		}
	}
	void Timer::stopCounting()
	{
		theTimeBeganToCount = false;
	}

	int Timer::getActualTime()
	{
		return (int)elapsedTime;
	}
	bool Timer::getTheTimeBeganToCount()
	{
		return theTimeBeganToCount;
	}


	void Timer::saveStartTimeReference()
	{
		auto start = steady_clock::now().time_since_epoch();
		startTimeReference = duration_cast<milliseconds>(start).count();
	}

	void Timer::saveElapsedTime()
	{
		elapsedTime = getElapsedTime();
		convertElapsedTimeToSeconds();
	}
	long long Timer::getElapsedTime()
	{
		return getTimeInThisFrame() - startTimeReference;
	}
	long long Timer::getTimeInThisFrame()
	{
		auto now = steady_clock::now().time_since_epoch();

		return duration_cast<milliseconds>(now).count();
	}
	void Timer::convertElapsedTimeToSeconds()
	{
		elapsedTime /= 1000;
	}
}
