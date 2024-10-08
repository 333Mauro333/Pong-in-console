#include "laser_pooling.h"


namespace pong_in_console
{
	Laser* LaserPooling::lasers[LaserPooling::amountOfLasers] = {};

	void LaserPooling::initLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i] = new Laser();
		}
	}
	void LaserPooling::updateLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i]->update();
		}
	}
	void LaserPooling::eraseLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i]->erase();
		}
	}
	void LaserPooling::drawLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i]->draw();
		}
	}
	void LaserPooling::destroyLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			delete lasers[i];
		}
	}

	void LaserPooling::deactivateAllLasers()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i]->deactivate();
		}
	}

	Laser* LaserPooling::getLaser()
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			if (!lasers[i]->getIsActive())
			{
				return lasers[i];
			}
		}

		return NULL;
	}
	vector<Laser*> LaserPooling::getActiveLasers()
	{
		vector<Laser*> activeLasers = vector<Laser*>();

		for (int i = 0; i < amountOfLasers; i++)
		{
			if (lasers[i]->getIsActive())
			{
				activeLasers.push_back(lasers[i]);
			}
		}

		return activeLasers;
	}
	void LaserPooling::setLasersLimits(Frame* frame)
	{
		for (int i = 0; i < amountOfLasers; i++)
		{
			lasers[i]->setMovementLimits(frame);
		}
	}
}
