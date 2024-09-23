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
		counter = 0;

		leftLimit = 0;
		rightLimit = ConsoleExt::getScreenWidth() - 1;
		lastMove = SIDE::NONE;

		initBullet();
	}
	Paddle::~Paddle()
	{
		delete bullet;
	}


	void Paddle::inputUpdate(int key)
	{
		if (canMove())
		{
			if (keyIsPressed(GAMEPLAY_CONTROLS::LEFT, key))
			{
				if (canGoLeft())
				{
					savePositionAsPrevious();

					moveLeft();
					resetCounter();
					saveLastMove(SIDE::LEFT);
				}
			}
			else if (keyIsPressed(GAMEPLAY_CONTROLS::RIGHT, key))
			{
				if (canGoRight())
				{
					savePositionAsPrevious();

					moveRight();
					resetCounter();
					saveLastMove(SIDE::RIGHT);
				}
			}
			else if (keyIsPressed(GAMEPLAY_CONTROLS::SHOOT, key))
			{
				shoot();
			}
		}
	}
	void Paddle::update()
	{
		if (!canMove())
		{
			discountCounter();
		}

		bullet->update();
	}
	void Paddle::erase()
	{
		GameObject::erase();

		bullet->erase();
	}
	void Paddle::draw()
	{
		drawNormal();

		bullet->draw();
	}

	Bullet* Paddle::getBullet()
	{
		return bullet;
	}
	void Paddle::setMovementLimits(Frame* frame)
	{
		leftLimit = frame->getLeft() + 1;
		rightLimit = frame->getRight() - 1;
	}

	bool Paddle::movedInThisFrame(SIDE sideToVerify)
	{
		return counter == delayToMove - 1 && lastMove == sideToVerify;
	}


	void Paddle::initBullet()
	{
		bullet = new Bullet();
	}

	bool Paddle::canMove()
	{
		return counter == 0;
	}
	bool Paddle::canGoLeft()
	{
		return position.x > leftLimit;
	}
	bool Paddle::canGoRight()
	{
		return position.x + size.w - 1 < rightLimit;
	}
	bool Paddle::keyIsPressed(GAMEPLAY_CONTROLS keyToVerify, int pressedKey)
	{
		return ControlsManager::isPressed(pressedKey, keyToVerify);
	}

	void Paddle::moveLeft()
	{
		position.x--;
	}
	void Paddle::moveRight()
	{
		position.x++;
	}
	void Paddle::shoot()
	{
		if (!bullet->getIsActive())
		{
			int centerPositionX = position.x + size.w / 2;

			bullet->setPosition(centerPositionX, position.y - 1);
			bullet->activate();
		}
	}

	void Paddle::resetCounter()
	{
		counter = delayToMove;
	}
	void Paddle::saveLastMove(SIDE lastMove)
	{
		this->lastMove = lastMove;
	}
	void Paddle::discountCounter()
	{
		counter--;
	}

	void Paddle::drawNormal()
	{
		COLOR previousColor = ConsoleExt::getForegroundColor();

		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::setForegroundColor(color);
		cout << "<=" << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << "=>";
		ConsoleExt::setForegroundColor(previousColor);
	}
}
