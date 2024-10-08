#ifndef LEVEL_TIME_MANAGER_H
#define LEVEL_TIME_MANAGER_H

#include "timer/timer.h"


namespace pong_in_console
{
	class LevelTimeManager
	{
	public:
		static void startCounting();
		static void updateTime();
		static void stopCounting();

		static int getActualTime();

	private:
		static Timer* timer;

		static bool Reached10Minutes();
	};
}

#endif // !LEVEL_TIME_MANAGER_H
