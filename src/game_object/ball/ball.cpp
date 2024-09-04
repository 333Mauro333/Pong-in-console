#include "ball.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Ball::Ball(int x, int y) : GameObject(x, y, 1, 1)
	{
		color = COLOR::C_LRED;
		delayToMove = 5;
		timer = 0;

		detectedCollision = false;

		speedX = 1;
		speedY = 1;

		externalLimits = {};
	}
	Ball::~Ball()
	{

	}


	void Ball::update()
	{
		if (timer == 0)
		{
			savePositionAsPrevious();

			timer = delayToMove;
			detectedCollision = false;

			applyMovement();
		}
		else
		{
			timer--;
		}
	}
	void Ball::draw()
	{
		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::writeWithColor("O", color);
	}

	void Ball::changeDirection(bool horizontal, bool vertical)
	{
		if (horizontal)
		{
			speedX = -speedX;
		}

		if (vertical)
		{
			speedY = -speedY;
		}
	}

	void Ball::setCollisionDetection()
	{
		detectedCollision = true;
	}
	void Ball::setMovementLimits(Frame* frame)
	{
		externalLimits.up = frame->getUp() + 1;
		externalLimits.down = frame->getDown() - 1;
		externalLimits.left = frame->getLeft() + 1;
		externalLimits.right = frame->getRight() - 1;
	}

	bool Ball::isCollisionDetected()
	{
		return detectedCollision;
	}
	bool Ball::isTimeToDetectCollision()
	{
		return timer == 0;
	}
	bool Ball::isItGoingDown()
	{
		return speedY > 0;
	}
	bool Ball::isItGoingRight()
	{
		return speedX > 0;
	}


	void Ball::applyMovement()
	{
		if (!canItGoUp() || !canItGoDown())
		{
			changeDirection(false, true);
		}

		if (!canItGoLeft() || !canItGoRight())
		{
			changeDirection(true, false);
		}

		position.x += speedX;
		position.y += speedY;
	}

	bool Ball::canItGoUp()
	{
		return position.y > externalLimits.up;
	}
	bool Ball::canItGoDown()
	{
		return position.y < externalLimits.down;
	}
	bool Ball::canItGoLeft()
	{
		return position.x > externalLimits.left;
	}
	bool Ball::canItGoRight()
	{
		return position.x < externalLimits.right;
	}
}
