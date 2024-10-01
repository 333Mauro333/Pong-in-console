#include "score_manager.h"


namespace pong_in_console
{
	int ScoreManager::levelScore = 0;
	int ScoreManager::totalScore = 0;


	void ScoreManager::addPoints(int points)
	{
		levelScore += points;
		totalScore += points;
	}
	void ScoreManager::resetLevelScore()
	{
		levelScore = 0;
	}
	void ScoreManager::resetTotalScore()
	{
		totalScore = 0;
	}

	int ScoreManager::getLevelScore()
	{
		return levelScore;
	}
	int ScoreManager::getTotalScore()
	{
		return totalScore;
	}
}
