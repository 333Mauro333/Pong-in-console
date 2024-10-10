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
		isTheFirstFrame = true;
		lastMove = SIDE::NONE;
		shotInThisFrame = false;

		initBullet();
	}
	Paddle::~Paddle()
	{
		delete bullet;
	}

	void Paddle::inputUpdate(int key)
	{
		shotInThisFrame = false;

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
				shootBullet();
				shootLasers();

				shotInThisFrame = true;
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
		if (thePositionChanged())
		{
			savePositionAsPrevious();
			drawWithGuns();
		}
		else if (isTheFirstFrame)
		{
			isTheFirstFrame = false;
			drawWithGuns();
		}

		bullet->draw();
	}

	POSITION Paddle::getCenterPosition()
	{
		POSITION positionToReturn = { position.x + size.w / 2, position.y };

		return positionToReturn;
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
	bool Paddle::getShotInThisFrame()
	{
		return shotInThisFrame;
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
	void Paddle::shootBullet()
	{
		if (!bullet->getIsActive())
		{
			int centerPositionX = position.x + size.w / 2;

			bullet->setPosition(centerPositionX, position.y - 1);
			bullet->activate();
		}
	}
	void Paddle::shootLasers()
	{
		Laser* laser1 = NULL;
		Laser* laser2 = NULL;


		laser1 = LaserPooling::getLaser();

		if (thereIsALaser(laser1))
		{
			laser1->activate();
		}

		laser2 = LaserPooling::getLaser();

		if (thereIsALaser(laser2))
		{
			laser2->activate();
		}

		if (thereIsALaser(laser1) && thereIsALaser(laser2))
		{
			shootALaser(laser1, SIDE::LEFT);
			shootALaser(laser2, SIDE::RIGHT);
		}
		else
		{
			if (thereIsALaser(laser1))
			{
				int randomValueBetween3and4 = rand() % (4 - 3 + 1) + 3;
				SIDE leftOrRightSide = (SIDE)randomValueBetween3and4;

				shootALaser(laser1, leftOrRightSide);
			}
			else if (thereIsALaser(laser2))
			{
				int randomValueBetween3and4 = rand() % (4 - 3 + 1) + 3;
				SIDE leftOrRightSide = (SIDE)randomValueBetween3and4;

				shootALaser(laser2, leftOrRightSide);
			}
		}
	}
	bool Paddle::thereIsALaser(Laser* laserToVerify)
	{
		return laserToVerify != NULL;
	}
	void Paddle::shootALaser(Laser* laser, SIDE side)
	{
		switch (side)
		{
		case SIDE::LEFT:
			laser->setPosition(position.x, position.y - 1);
			break;

		case SIDE::RIGHT:
			laser->setPosition(getRight(), position.y - 1);
			break;
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
		// 205: ═
		// 202: ╩
		COLOR previousColor = ConsoleExt::getForegroundColor();

		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::setForegroundColor(color);
		cout << "<=" << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << "=>";
		ConsoleExt::setForegroundColor(previousColor);
	}
	void Paddle::drawWithGuns()
	{
		// 200: ╚
		// 188: ╝
		COLOR previousColor = ConsoleExt::getForegroundColor();

		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::setForegroundColor(color);
		cout << (char)200 << "=" << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << "=" << (char)188;
		ConsoleExt::setForegroundColor(previousColor);
	}
}
