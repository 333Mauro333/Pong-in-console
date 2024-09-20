#ifndef PADDLE_H
#define PADDLE_H

#include "mgtv_library.h"
#include "raylib.h"

#include "enums/side.h"
#include "game_object/bullet/bullet.h"
#include "game_object/game_object.h"
#include "interface_simulation/limited_element/limited_element.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Paddle : public GameObject, public LimitedElement
	{
	public:
		Paddle(int x, int y);
		~Paddle();

		void inputUpdate(int key);
		void update();
		void erase() override;
		void draw() override;

		void setMovementLimits(Frame* frame) override;

		bool itMovedInThisFrame(SIDE sideToVerify);

	private:
		COLOR color;
		int delayToMove;
		int timer;

		int leftLimit;
		int rightLimit;

		SIDE movedDirection;

		Bullet* bullet;

		void shoot();

		bool canItGoLeft();
		bool canItGoRight();

		void drawNormal();
	};
}

#endif // !PADDLE_H
