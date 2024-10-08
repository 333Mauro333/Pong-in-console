#include "level_time_manager.h"


namespace pong_in_console
{
	Timer* LevelTimeManager::timer = new Timer();

	void LevelTimeManager::startCounting()
	{
		timer->startCounting();
	}
	void LevelTimeManager::updateTime()
	{
		timer->updateTime();
	}
	void LevelTimeManager::stopCounting()
	{
		timer->stopCounting();
	}

	int LevelTimeManager::getActualTime()
	{
		return timer->getActualTime();
	}
}
