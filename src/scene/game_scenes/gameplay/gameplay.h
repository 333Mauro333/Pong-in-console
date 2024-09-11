#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "game_object/ball/ball.h"
#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/paddle/paddle.h"
#include "game_object/frame/frame.h"
#include "scene/scene.h"


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
		Paddle* player;
		Ball* ball;
		Frame* frame;

		static const int blocksAmount = 1;
		Block* blocks[blocksAmount];

		void checkBallCollisions();
	};
}

#endif // !GAMEPLAY_H
