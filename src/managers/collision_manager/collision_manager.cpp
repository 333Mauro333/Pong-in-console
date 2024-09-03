#include "collision_manager.h"


namespace pong_in_console
{
	bool CollisionManager::isColliding(Paddle* paddle, Ball* ball)
	{
		return ball->isItGoingDown() &&
			   ball->isTimeToDetectCollision() && !ball->isCollisionDetected() &&
			   ball->getPosition().x >= paddle->getPosition().x &&
			   ball->getPosition().x <= paddle->getPosition().x + paddle->getSize().w - 1 &&
			   ball->getPosition().y == paddle->getPosition().y - 1;
	}
}
