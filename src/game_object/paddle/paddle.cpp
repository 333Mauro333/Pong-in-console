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

		initBullet();
		initLasers(4);
		initLifeController();
	}
	Paddle::~Paddle()
	{
		for (int i = 0; i < lasers.size(); i++)
		{
			delete lasers[i];
		}

		delete bullet;
		delete lifeController;
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
				shootBullet();
				shootLasers();
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

		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->update();
		}
	}
	void Paddle::erase()
	{
		GameObject::erase();

		bullet->erase();

		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->erase();
		}
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

		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->draw();
		}
	}

	Bullet* Paddle::getBullet()
	{
		return bullet;
	}
	LifeController* Paddle::getLifeController()
	{
		return lifeController;
	}
	vector<Laser*> Paddle::getActiveLasers()
	{
		vector<Laser*> activeLasers = vector<Laser*>();

		for (int i = 0; i < lasers.size(); i++)
		{
			if (lasers[i]->getIsActive())
			{
				activeLasers.push_back(lasers[i]);
			}
		}

		return activeLasers;
	}
	void Paddle::setMovementLimits(Frame* frame)
	{
		leftLimit = frame->getLeft() + 1;
		rightLimit = frame->getRight() - 1;

		for (int i = 0; i < lasers.size(); i++)
		{
			lasers[i]->setMovementLimits(frame);
		}
	}

	bool Paddle::movedInThisFrame(SIDE sideToVerify)
	{
		return counter == delayToMove - 1 && lastMove == sideToVerify;
	}


	void Paddle::initBullet()
	{
		bullet = new Bullet();
	}
	void Paddle::initLasers(int amountOfLasers)
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers.push_back(new Laser());
		}
	}
	void Paddle::initLifeController()
	{
		lifeController = new LifeController();
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


		laser1 = getInactiveLaser();

		if (thereIsALaser(laser1))
		{
			laser1->activate();
		}

		laser2 = getInactiveLaser();

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
	Laser* Paddle::getInactiveLaser()
	{
		for (int i = 0; i < lasers.size(); i++)
		{
			if (!lasers[i]->getIsActive())
			{
				return lasers[i];
			}
		}

		return NULL;
	}
	bool Paddle::thereIsALaser(Laser* laserToVerify)
	{
		return laserToVerify != NULL;
	}
	void Paddle::shootALaser(Laser* laser, SIDE side)
	{
		laser->activate();

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
