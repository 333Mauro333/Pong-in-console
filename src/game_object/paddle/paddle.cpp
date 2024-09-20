#include "paddle.h"

#include <iostream>

#include "managers/controls_manager/controls_manager.h"

using mgtv_library::console::ConsoleExt;
using std::cout;


namespace pong_in_console
{
	Paddle::Paddle(int x, int y) : GameObject(x, y, 9, 1)
	{
		color = COLOR::C_WHITE;
		delayToMove = 3;
		timer = 0;

		leftLimit = 0;
		rightLimit = ConsoleExt::getScreenWidth() - 1;

		movedDirection = SIDE::NONE;
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
					movedDirection = SIDE::LEFT;
				}
			}
			else if (ControlsManager::isPressed(key, GAMEPLAY_CONTROLS::RIGHT))
			{
				if (canItGoRight())
				{
					position.x++;
					timer = delayToMove;
					movedDirection = SIDE::RIGHT;
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

		drawNormal();
	}

	void Paddle::setMovementLimits(Frame* frame)
	{
		leftLimit = frame->getLeft() + 1;
		rightLimit = frame->getRight() - 1;
	}

	bool Paddle::itMovedInThisFrame(SIDE sideToVerify)
	{
		return timer == delayToMove - 1 && movedDirection == sideToVerify;
	}


	bool Paddle::canItGoLeft()
	{
		return position.x > leftLimit;
	}
	bool Paddle::canItGoRight()
	{
		return position.x + size.w - 1 < rightLimit;
	}

	void Paddle::drawNormal()
	{
		COLOR previousColor = ConsoleExt::getForegroundColor();

		ConsoleExt::setForegroundColor(color);
		cout << "<=" << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << "=>";
		ConsoleExt::setForegroundColor(previousColor);
	}
}
