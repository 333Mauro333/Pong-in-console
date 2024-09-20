#include "bullet.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Bullet::Bullet() : GameObject(0, 0)
	{
		color = COLOR::C_WHITE;
		delayToMove = 2;
		timer = delayToMove;

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
			if (timer <= 0)
			{
				savePositionAsPrevious();

				timer = delayToMove;
				position.y--;
				reachedDistance++;

				if (reachedDistance >= maxDistance)
				{
					resetValues();
					deactivate();
				}
			}
			else
			{
				timer--;
			}
		}
	}
	void Bullet::draw()
	{
		if (isActive)
		{
			drawBullet();
		}
	}


	void Bullet::resetValues()
	{
		reachedDistance = 0;
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
