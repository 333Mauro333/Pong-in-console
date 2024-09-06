#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "enums/ball_collision_type.h"
#include "enums/side.h"
#include "game_object/ball/ball.h"
#include "game_object/paddle/paddle.h"


namespace pong_in_console
{
	class CollisionManager
	{
	public:
		static BALL_COLLISION_TYPE getBallCollisionType(Paddle* paddle, Ball* ball);

	private:
		static bool IsTheBallInPaddleRange(Paddle* paddle, Ball* ball);
		static bool ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction);
		static bool IsTheBallOverThePaddle(Paddle* paddle, Ball* ball);
	};
}

#endif // !COLLISION_MANAGER_H
