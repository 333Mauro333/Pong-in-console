#ifndef PADDLE_H
#define PADDLE_H

#include <vector>

#include "mgtv_library.h"
#include "raylib.h"

#include "enums/gameplay_controls.h"
#include "enums/side.h"
#include "game_object/bullet/bullet.h"
#include "game_object/game_object.h"
#include "game_object/laser/laser.h"
#include "interface_simulation/limited_element/limited_element.h"
#include "life_controller/life_cotroller.h"

using std::vector;
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
		vector<Laser*> getActiveLasers();
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
		vector<Laser*> lasers;
		
		LifeController* lifeController;

		void initBullet();
		void initLasers(int amountOfLasers);
		void initLifeController();

		bool canMove();
		bool canGoLeft();
		bool canGoRight();
		bool keyIsPressed(GAMEPLAY_CONTROLS keyToVerify, int pressedKey);

		void moveLeft();
		void moveRight();
		void shootBullet();
		void shootLasers();
		Laser* getInactiveLaser();
		bool thereIsALaser(Laser* laserToVerify);
		void shootALaser(Laser* laser, SIDE side);

		void resetCounter();
		void saveLastMove(SIDE lastMove);
		void discountCounter();

		void drawNormal();
		void drawWithGuns();
	};
}

#endif // !PADDLE_H
