#ifndef PADDLE_H
#define PADDLE_H

#include "mgtv_library.h"
#include "raylib.h"

#include "enums/gameplay_controls.h"
#include "enums/side.h"
#include "game_object/bullet/bullet.h"
#include "game_object/game_object.h"
#include "interface_simulation/limited_element/limited_element.h"
#include "life_controller/life_cotroller.h"

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

		Bullet* getBullet();
		LifeController* getLifeController();
		void setMovementLimits(Frame* frame) override;

		bool movedInThisFrame(SIDE sideToVerify);

	private:
		COLOR color;
		int delayToMove;
		int counter;

		int leftLimit;
		int rightLimit;
		bool isTheFirstFrame;
		SIDE lastMove;

		Bullet* bullet;
		LifeController* lifeController;

		void initBullet();
		void initLifeController();

		bool canMove();
		bool canGoLeft();
		bool canGoRight();
		bool keyIsPressed(GAMEPLAY_CONTROLS keyToVerify, int pressedKey);

		void moveLeft();
		void moveRight();
		void shoot();

		void resetCounter();
		void saveLastMove(SIDE lastMove);
		void discountCounter();

		void drawNormal();
	};
}

#endif // !PADDLE_H
