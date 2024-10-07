#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

namespace pong_in_console
{
	class ScoreManager
	{
	public:
		static void addBlocksPoints(int points);
		static void resetBlocksScore();
		static void resetTotalScore();

		static int getBlocksScore();
		static int getTotalScore();

		static void saveBlocksScore(int score);
		static void saveTotalScore(int score);

	private:
		static int blocksScore;
		static int totalScore;
	};
}

#endif // !SCORE_MANAGER_H
