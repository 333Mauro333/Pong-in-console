#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "game_object/ball/ball.h"
#include "game_object/paddle/paddle.h"


namespace pong_in_console
{
	class CollisionManager
	{
	public:
		static bool isColliding(Paddle* paddle, Ball* ball);

	private:

	};
}

#endif // !COLLISION_MANAGER_H
