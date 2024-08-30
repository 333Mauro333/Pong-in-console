#include "ball.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Ball::Ball(int x, int y) : GameObject(x, y, 1, 1)
	{
		color = COLOR::C_LRED;
		delayToMove = 10;
		timer = 0;

		speedX = 1;
		speedY = 1;
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

			position.x += speedX;
			position.y += speedY;

			if (position.y == 0 || position.y == 10)
			{
				changeDirection(false, true);
			}

			if (position.x == ConsoleExt::getScreenWidth() - 1 || position.x == 0)
			{
				changeDirection(true, false);
			}
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
}
