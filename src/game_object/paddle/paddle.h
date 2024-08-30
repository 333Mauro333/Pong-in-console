#ifndef PADDLE_H
#define PADDLE_H

#include "game_object/game_object.h"

#include "raylib.h"
#include "mgtv_library.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Paddle : public GameObject
	{
	public:
		Paddle(int x, int y);
		~Paddle();

		void inputUpdate(int key);
		void update();
		void draw() override;

	private:
		COLOR color;
		int delayToMove;
		int timer;
	};
}

#endif // !PADDLE_H
