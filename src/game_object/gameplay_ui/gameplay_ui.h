#ifndef GAMEPLAY_UI_H
#define GAMEPLAY_UI_H

#include "enums/gameplay_statistic.h"
#include "game_object/frame/frame.h"
#include "game_object/game_object.h"


namespace pong_in_console
{
	class GameplayUI : public GameObject
	{
	public:
		GameplayUI(Frame* frame, int height);
		~GameplayUI();

		void pointToLives(int& lives);
		void pointToLevel(int& level);
		void pointToScore(int& score);
		void pointToTime(int& time);

		void updateStatistic(GAMEPLAY_STATISTIC statisticToUpdate);

		void draw() override;

	private:
		int* lives;
		int* level;
		int* score;
		int* time;

		bool itWasDrown;
		bool updateLives;
		bool updateLevel;
		bool updateTime;
		bool updateScore;

		void drawFrame();
		void drawLeftBorderConection();
		void drawRightBorderConection();
		void drawColumn(int positionXOverTheFrame);

		void writeLives();
		void writeLevel();
		void writeTime();
		void writeMinutesAndSeconds();
		void writeScore();
		void writeScoreWithZeros(int amountOfZeros);
	};
}

#endif // !GAMEPLAY_UI_H
