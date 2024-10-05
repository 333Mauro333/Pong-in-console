#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

namespace pong_in_console
{
	class ScoreManager
	{
	public:
		static void addPoints(int points);
		static void resetLevelScore();
		static void resetTotalScore();

		static int getLevelScore();
		static int getTotalScore();

		static void saveLevelScore(int score);
		static void saveTotalScore(int score);

	private:
		static int levelScore;
		static int totalScore;
	};
}

#endif // !SCORE_MANAGER_H
