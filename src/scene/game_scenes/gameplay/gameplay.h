#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "game_object/paddle/paddle.h"
#include "game_object/ball/ball.h"
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
	};
}

#endif // !GAMEPLAY_H
