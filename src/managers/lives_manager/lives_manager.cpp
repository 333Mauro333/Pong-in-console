#include "lives_manager.h"


namespace pong_in_console
{
	int LivesManager::lives = 0;

	void LivesManager::addALife()
	{
		lives++;
	}
	void LivesManager::discountALife()
	{
		lives--;
	}

	int LivesManager::getLives()
	{
		return lives;
	}
	void LivesManager::setLives(int lives)
	{
		LivesManager::lives = lives;
	}

	bool LivesManager::thereAreLives()
	{
		return lives >= 0;
	}
}
