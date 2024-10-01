#include "level_manager.h"


namespace pong_in_console
{
	int LevelManager::gameLevel = 1;

	void LevelManager::addLevel()
	{
		gameLevel++;
	}

	int LevelManager::getLevel()
	{
		return gameLevel;
	}
	void LevelManager::setLevel(int newLevel)
	{
		gameLevel = newLevel;
	}
}
