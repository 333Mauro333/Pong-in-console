#include "time_manager.h"

#include <chrono>
#include <thread>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;


namespace pong_in_console
{
	long long TimeManager::startTimeReference = 0;
	long long TimeManager::elapsedTime = 0;
	bool TimeManager::theTimeBeganToCount = false;


	void TimeManager::startCounting()
	{
		theTimeBeganToCount = true;

		saveStartTimeReference();
	}
	void TimeManager::updateTime()
	{
		if (theTimeBeganToCount)
		{
			saveElapsedTime();
		}
	}
	void TimeManager::stopCounting()
	{
		theTimeBeganToCount = false;
	}

	int TimeManager::getActualTime()
	{
		return (int)elapsedTime;
	}
	bool TimeManager::getTheTimeBeganToCount()
	{
		return theTimeBeganToCount;
	}


	void TimeManager::saveStartTimeReference()
	{
		auto start = steady_clock::now().time_since_epoch();
		startTimeReference = duration_cast<milliseconds>(start).count();
	}

	void TimeManager::saveElapsedTime()
	{
		elapsedTime = getElapsedTime();
		convertElapsedTimeToSeconds();
	}
	long long TimeManager::getElapsedTime()
	{
		return getTimeInThisFrame() - startTimeReference;
	}
	long long TimeManager::getTimeInThisFrame()
	{
		auto now = steady_clock::now().time_since_epoch();

		return duration_cast<milliseconds>(now).count();
	}
	void TimeManager::convertElapsedTimeToSeconds()
	{
		elapsedTime /= 1000;
	}
}
