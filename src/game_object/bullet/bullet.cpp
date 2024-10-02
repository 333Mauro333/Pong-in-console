#include "bullet.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Bullet::Bullet() : GameObject(0, 0)
	{
		color = COLOR::C_GRAY;
		delayToMove = 2;
		counter = delayToMove;

		maxDistance = 5;
		reachedDistance = 0;

		deactivate();
	}
	Bullet::~Bullet()
	{

	}


	void Bullet::update()
	{
		if (isActive)
		{
			if (isTimeToMove())
			{
				savePositionAsPrevious();

				resetCounter();
				moveUp();
				incrementReachedDistance();

				if (itReachedMaxDistance())
				{
					impact();
				}
			}
			else
			{
				discountCounter();
			}
		}
	}
	void Bullet::draw()
	{
		if (movedInThisFrame() && isActive)
		{
			drawBullet();
		}
	}

	void Bullet::impact()
	{
		resetReachedDistance();
		deactivate();
	}


	bool Bullet::isTimeToMove()
	{
		return counter <= 0;
	}
	void Bullet::resetCounter()
	{
		counter = delayToMove;
	}
	void Bullet::moveUp()
	{
		position.y--;
	}
	void Bullet::incrementReachedDistance()
	{
		reachedDistance++;
	}

	bool Bullet::itReachedMaxDistance()
	{
		return reachedDistance >= maxDistance;
	}
	void Bullet::resetReachedDistance()
	{
		reachedDistance = 0;
	}
	void Bullet::discountCounter()
	{
		counter--;
	}

	bool Bullet::movedInThisFrame()
	{
		return counter == delayToMove;
	}
	void Bullet::drawBullet()
	{
		string bulletPicture = "";
		char bulletChar = (char)250; // ·

		bulletPicture += bulletChar;

		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::writeWithColor(bulletPicture, color);
	}
}
