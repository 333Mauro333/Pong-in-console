#include "collision_manager.h"


namespace pong_in_console
{
	BALL_COLLISION_TYPE CollisionManager::getBallCollisionType(Paddle* paddle, Ball* ball)
	{
		if (IsTheBallInPaddleRange(paddle, ball))
		{
			if (ballCollidesInPaddleCorner(paddle, ball, SIDE::LEFT))
			{
				return BALL_COLLISION_TYPE::PAD_CORNER_LEFT;
			}
			else if (ballCollidesInPaddleCorner(paddle, ball, SIDE::RIGHT))
			{
				return BALL_COLLISION_TYPE::PAD_CORNER_RIGHT;
			}
			else if (IsTheBallOverThePaddle(paddle, ball))
			{
				return BALL_COLLISION_TYPE::PAD_SURFACE;
			}
		}

		return BALL_COLLISION_TYPE::NONE;
	}

	bool CollisionManager::IsTheBallInPaddleRange(Paddle* paddle, Ball* ball)
	{
		return ball->isItGoingDown() && ball->isTimeToDetectCollision() &&
			   ball->getPosition().y == paddle->getPosition().y - 1 &&
			   ball->getPosition().x >= paddle->getLeft() - 1 &&
			   ball->getPosition().x <= paddle->getRight() + 1;
	}
	bool CollisionManager::ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction)
	{
		switch (direction)
		{
		case SIDE::LEFT:
			return ball->getPosition().x == paddle->getLeft() - 1 &&
				   ball->isItGoingRight();

		case SIDE::RIGHT:
		default:
			return ball->getPosition().x == paddle->getRight() + 1 &&
				   !ball->isItGoingRight();
		}
	}
	bool CollisionManager::IsTheBallOverThePaddle(Paddle* paddle, Ball* ball)
	{
		return ball->getPosition().x >= paddle->getLeft() &&
			   ball->getPosition().x <= paddle->getRight();
	}
}
