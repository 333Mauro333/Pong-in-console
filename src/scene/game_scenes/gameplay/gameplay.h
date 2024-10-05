#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>

#include "game_object/ball/ball.h"
#include "game_object/block/block.h"
#include "game_object/frame/frame.h"
#include "game_object/gameplay_ui/gameplay_ui.h"
#include "game_object/paddle/paddle.h"
#include "scene/scene.h"
#include "timer/timer.h"

using std::vector;


namespace pong_in_console
{
	class Gameplay : public Scene
	{
	public:
		Gameplay();
		~Gameplay();

		void inputUpdate(int key) override;
		void update() override;
		void erase() override;
		void draw() override;

	private:
		int levelScore;
		int totalScore;
		int level;
		int time;
		bool isTimeToChangeScene;

		Paddle* player;
		Ball* ball;
		Frame* frame;
		Timer* timer;
		GameplayUI* ui;

		vector<Block*> blocks;

		void initPlayer();
		void initBall();
		void initFrame();
		void initBlocks();
		void initUI();
		void setLaserLimits();

		void updateLasers();
		void eraseLasers();
		void drawLasers();
		void drawBlocks();
		void deleteBlocks();

		void checkMenuInput(int key);
		void checkBallCollisions();
		void checkLaserCollisions();

		int getAmountOfActiveBlocks();
		void disappearABlock();

		bool theOneBallTouchesTheFloor();
		void discountALife();
		bool thereAreLives();
		void putTheBallOverThePaddle();

		bool theSecondsChanged();
		void updateTime();

		bool allTheBlocksWereBroken();
	};
}

#endif // !GAMEPLAY_H
