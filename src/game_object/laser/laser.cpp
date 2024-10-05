#include "laser.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Laser::Laser() : GameObject(0, 0)
	{
		color = COLOR::C_LBLUE;
		delayToMove = 2;
		counter = delayToMove;

		yLimit = 0;

		deactivate();
	}
	Laser::~Laser()
	{

	}

	void Laser::update()
	{
		if (isActive)
		{
			if (isTimeToMove())
			{
				savePositionAsPrevious();

				resetCounter();
				moveUp();

				if (itReachedTheLimit())
				{
					moveDown();
					impact();
				}
			}
			else
			{
				discountCounter();
			}
		}
	}
	void Laser::draw()
	{
		if (movedInThisFrame() && isActive)
		{
			drawLaser();
		}
	}

	void Laser::impact()
	{
		deactivate();
	}

	void Laser::setMovementLimits(Frame* frame)
	{
		yLimit = frame->getUp();
	}


	bool Laser::isTimeToMove()
	{
		return counter <= 0;
	}
	void Laser::resetCounter()
	{
		counter = delayToMove;
	}
	void Laser::moveUp()
	{
		position.y--;
	}
	void Laser::moveDown()
	{
		position.y++;
	}
	bool Laser::itReachedTheLimit()
	{
		return position.y == yLimit;
	}
	void Laser::discountCounter()
	{
		counter--;
	}

	bool Laser::movedInThisFrame()
	{
		return counter == delayToMove;
	}
	void Laser::drawLaser()
	{
		string laserPicture = "";
		char laserChar = (char)179; // │

		laserPicture += laserChar;

		ConsoleExt::goToCoordinates(position.x, position.y);
		ConsoleExt::writeWithColor(laserPicture, color);
	}
}
