#include "paddle.h"

#include "managers/controls_manager/controls_manager.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Paddle::Paddle(int x, int y) : GameObject(x, y, 10, 1)
	{
		color = COLOR::C_RED;
		delayToMove = 5;
		timer = 0;

		leftLimit = 0;
		rightLimit = ConsoleExt::getScreenWidth() - 1;
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
				if (canItGoLeft())
				{
					position.x--;
					timer = delayToMove;
				}
			}

			if (ControlsManager::isPressed(key, GAMEPLAY_CONTROLS::RIGHT))
			{
				if (canItGoRight())
				{
					position.x++;
					timer = delayToMove;
				}
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

	void Paddle::setMovementLimits(Frame* frame)
	{
		leftLimit = frame->getLeft() + 1;
		rightLimit = frame->getRight() - 1;
	}


	bool Paddle::canItGoLeft()
	{
		return position.x > leftLimit;
	}
	bool Paddle::canItGoRight()
	{
		return position.x + size.w - 1 < rightLimit;
	}
}
