#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>

#include "game_object/ball/ball.h"
#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/frame/frame.h"
#include "game_object/paddle/paddle.h"
#include "scene/scene.h"

using std::vector;


namespace pong_in_console
{
	class Gameplay : public Scene
	{
	public:
		Gameplay(int levelNumber);
		~Gameplay();

		void inputUpdate(int key) override;
		void update() override;
		void erase() override;
		void draw() override;

	private:
		Paddle* player;
		Ball* ball;
		Frame* frame;

		vector<Block*> blocks;

		void checkBallCollisions();
	};
}

#endif // !GAMEPLAY_H
