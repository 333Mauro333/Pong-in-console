#include "ball.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Ball::Ball(int x, int y, BALL_DIRECTION ballDirection) : GameObject(x, y, 1, 1)
	{
		color = COLOR::C_LRED;
		delayToMove = 50;
		timer = 0;

		switch (ballDirection)
		{
		case BALL_DIRECTION::UP_LEFT:
			speedX = -1;
			speedY = -1;
			break;

		case BALL_DIRECTION::UP_RIGHT:
			speedX = 1;
			speedY = -1;
			break;

		case BALL_DIRECTION::DOWN_LEFT:
			speedX = -1;
			speedY = 1;
			break;

		case BALL_DIRECTION::DOWN_RIGHT:
		default:
			speedX = 1;
			speedY = 1;
			break;
		}

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

	void Ball::invertDirection(bool horizontal, bool vertical)
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
	void Ball::setDirection(BALL_DIRECTION ballDirection)
	{
		switch (ballDirection)
		{
		case BALL_DIRECTION::UP_LEFT:
			speedX = -1;
			speedY = -1;
			break;

		case BALL_DIRECTION::UP_RIGHT:
			speedX = 1;
			speedY = -1;
			break;

		case BALL_DIRECTION::DOWN_LEFT:
			speedX = -1;
			speedY = 1;
			break;

		case BALL_DIRECTION::DOWN_RIGHT:
			speedX = 1;
			speedY = 1;
			break;
		}
	}

	BALL_DIRECTION Ball::getBallDirection()
	{
		if (speedX < 0 && speedY < 0)
		{
			return BALL_DIRECTION::UP_LEFT;
		}
		else if (speedX > 0 && speedY < 0)
		{
			return BALL_DIRECTION::UP_RIGHT;
		}
		else if (speedX < 0 && speedY > 0)
		{
			return BALL_DIRECTION::DOWN_LEFT;
		}
		else
		{
			return BALL_DIRECTION::DOWN_RIGHT;
		}
	}

	void Ball::setPosition(int x, int y)
	{
		position = { x, y };

		if (x < externalLimits.left)
		{
			position.x = externalLimits.left;
		}
		else if (x > externalLimits.right)
		{
			position.x = externalLimits.right;
		}
	}
	void Ball::setMovementLimits(Frame* frame)
	{
		externalLimits.up = frame->getUp() + 1;
		externalLimits.down = frame->getDown() - 1;
		externalLimits.left = frame->getLeft() + 1;
		externalLimits.right = frame->getRight() - 1;
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
			invertDirection(false, true);
		}

		if (!canItGoLeft() || !canItGoRight())
		{
			invertDirection(true, false);
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
