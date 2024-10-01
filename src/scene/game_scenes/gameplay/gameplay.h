#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>

#include "game_object/ball/ball.h"
#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/frame/frame.h"
#include "game_object/gameplay_ui/gameplay_ui.h"
#include "game_object/paddle/paddle.h"
#include "scene/scene.h"

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
		long long time;

		Paddle* player;
		Ball* ball;
		Frame* frame;
		GameplayUI* ui;

		vector<Block*> blocks;

		void initPlayer();
		void initBall();
		void initFrame();
		void initBlocks();
		void initUI();

		void checkMenuInput(int key);
		void checkBallCollisions();
	};
}

#endif // !GAMEPLAY_H
