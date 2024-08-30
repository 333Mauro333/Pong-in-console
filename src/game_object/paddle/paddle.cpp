#include "paddle.h"

#include "managers/controls_manager/controls_manager.h"

#include <iostream>


namespace pong_in_console
{
	Paddle::Paddle(int x, int y) : GameObject(x, y, 10, 1)
	{
		color = COLOR::C_RED;
		delayToMove = 5;
		timer = 0;
	}
	Paddle::~Paddle()
	{

	}

	void Paddle::inputUpdate(int key)
	{
		if (timer == 0)
		{
			savePositionAsPrevious();

			if (ControlsManager::isPressed(key, GAMEPLAY_CONTROLS::LEFT))
			{
				position.x--;
				timer = delayToMove;
			}

			if (ControlsManager::isPressed(key, GAMEPLAY_CONTROLS::RIGHT))
			{
				position.x++;
				timer = delayToMove;
			}
		}
	}
	void Paddle::update()
	{
		if (timer > 0)
		{
			timer--;
		}
	}
	void Paddle::draw()
	{
		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::writeWithColor("<========>", color);
	}
}
