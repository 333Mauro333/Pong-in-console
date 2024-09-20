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

	private:
		COLOR color;
		int delayToMove;
		int timer;

		int maxDistance;
		int reachedDistance;

		void resetValues();
		void drawBullet();
	};
}

#endif // !BULLET_H
