#include "score_manager.h"


namespace pong_in_console
{
	int ScoreManager::blocksScore = 0;
	int ScoreManager::totalScore = 0;

	void ScoreManager::addBlocksPoints(int points)
	{
		blocksScore += points;
		totalScore += points;
	}
	void ScoreManager::resetBlocksScore()
	{
		blocksScore = 0;
	}
	void ScoreManager::resetTotalScore()
	{
		totalScore = 0;
	}

	int ScoreManager::getBlocksScore()
	{
		return blocksScore;
	}
	int ScoreManager::getTotalScore()
	{
		return totalScore;
	}

	void ScoreManager::saveBlocksScore(int score)
	{
		blocksScore = score;
	}
	void ScoreManager::saveTotalScore(int score)
	{
		totalScore = score;
	}
}
