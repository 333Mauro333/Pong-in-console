#include "ball.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Ball::Ball(int x, int y, BALL_DIRECTION ballDirection) : GameObject(x, y, 1, 1)
	{
		color = COLOR::C_LRED;
		delayToMove = 10;
		counter = 0;
		isTheFirstFrame = true;

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

		isInStoppedMode = false;

		externalLimits.up = 0;
		externalLimits.down = ConsoleExt::getScreenHeight() - 1;
		externalLimits.left = 0;
		externalLimits.right = ConsoleExt::getScreenWidth() - 1;

		paddleReference = NULL;
	}
	Ball::~Ball()
	{

	}

	void Ball::update()
	{
		if (!isInStoppedMode)
		{
			if (isTimeToMove())
			{
				savePositionAsPrevious();

				resetCounter();
				applyMovement();
			}
			else
			{
				discountCounter();
			}
		}
		else if (paddleReference != NULL)
		{
			POSITION newPosition = { paddleReference->getCenterPosition().x, paddleReference->getCenterPosition().y - 1 };

			if (paddleReference->movedInThisFrame(SIDE::LEFT))
			{
				savePositionAsPrevious();

				setPosition(newPosition);
				setDirection(BALL_DIRECTION::UP_LEFT);
			}
			else if (paddleReference->movedInThisFrame(SIDE::RIGHT))
			{
				savePositionAsPrevious();

				setPosition(newPosition);
				setDirection(BALL_DIRECTION::UP_RIGHT);
			}
			else if (paddleReference->getShotInThisFrame())
			{
				isInStoppedMode = false;
			}
		}
	}
	void Ball::draw()
	{
		if ((movedInThisFrame() || isInStoppedMode) && isActive)
		{
			ConsoleExt::goToCoordinates(position.x, position.y);
			ConsoleExt::writeWithColor("O", color);
		}
		else if (isTheFirstFrame)
		{
			isTheFirstFrame = false;
			ConsoleExt::goToCoordinates(position.x, position.y);
			ConsoleExt::writeWithColor("O", color);
		}
	}

	void Ball::redirectInLimits()
	{
		if (!canGoUp() || !canGoDown())
		{
			invertDirection(false, true);
		}

		if (!canGoLeft() || !canGoRight())
		{
			invertDirection(true, false);
		}
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
	bool Ball::getIsInStoppedMode()
	{
		return isInStoppedMode;
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
	void Ball::setPosition(POSITION position)
	{
		this->position = position;

		if (this->position.x < externalLimits.left)
		{
			this->position.x = externalLimits.left;
		}
		else if (this->position.x > externalLimits.right)
		{
			this->position.x = externalLimits.right;
		}
	}
	void Ball::setIsInStoppedMode(bool isInStoppedMode)
	{
		this->isInStoppedMode = isInStoppedMode;
	}
	void Ball::setMovementLimits(Frame* frame)
	{
		externalLimits.up = frame->getUp() + 1;
		externalLimits.down = frame->getDown() - 1;
		externalLimits.left = frame->getLeft() + 1;
		externalLimits.right = frame->getRight() - 1;
	}
	void Ball::setPaddleReference(Paddle* paddleReference)
	{
		this->paddleReference = paddleReference;
	}

	bool Ball::isTimeToDetectCollision()
	{
		return counter == 0;
	}
	bool Ball::isGoingDown()
	{
		return speedY > 0;
	}
	bool Ball::isGoingRight()
	{
		return speedX > 0;
	}
	bool Ball::canGoUp()
	{
		return position.y > externalLimits.up;
	}
	bool Ball::canGoDown()
	{
		return position.y < externalLimits.down;
	}
	bool Ball::canGoLeft()
	{
		return position.x > externalLimits.left;
	}
	bool Ball::canGoRight()
	{
		return position.x < externalLimits.right;
	}


	bool Ball::isTimeToMove()
	{
		return counter == 0;
	}
	bool Ball::movedInThisFrame()
	{
		return counter == delayToMove;
	}
	void Ball::resetCounter()
	{
		counter = delayToMove;
	}
	void Ball::discountCounter()
	{
		counter--;
	}

	void Ball::applyMovement()
	{
		position.x += speedX;
		position.y += speedY;

		redirectInLimits();
	}
}
