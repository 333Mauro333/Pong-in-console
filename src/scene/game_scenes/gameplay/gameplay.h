#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "scene/scene.h"

#include "game_object/paddle/paddle.h"


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
	};
}

#endif // !GAMEPLAY_H
