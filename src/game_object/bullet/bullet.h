#ifndef BULLET_H
#define BULLET_H

#include "mgtv_library.h"

#include "game_object/game_object.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		~Bullet();

		void update();
		void draw() override;

		void impact();

	private:
		COLOR color;
		int delayToMove;
		int counter;

		int maxDistance;
		int reachedDistance;

		bool isTimeToMove();
		void resetCounter();
		void moveUp();
		void incrementReachedDistance();

		bool itReachedMaxDistance();
		void resetReachedDistance();
		void discountCounter();

		void drawBullet();
	};
}

#endif // !BULLET_H
