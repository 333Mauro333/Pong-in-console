#include "laser_pooling.h"


namespace pong_in_console
{
	LaserPooling* LaserPooling::instance = NULL;

	LaserPooling* LaserPooling::getInstance()
	{
		return instance;
	}

	LaserPooling::LaserPooling(int amountOfLasers)
	{
		laserVector = vector<Laser*>();

		if (instance == NULL)
		{
			instance = this;

			for (int i = 0; i < amountOfLasers; i++)
			{
				laserVector.push_back(new Laser());
			}
		}
		else
		{
			delete this;
		}
	}
	LaserPooling::~LaserPooling()
	{
		for (int i = 0; i < laserVector.size(); i++)
		{
			delete laserVector[i];
		}
	}

	Laser* LaserPooling::getLaser()
	{
		for (int i = 0; i < laserVector.size(); i++)
		{
			if (!laserVector[i]->getIsActive())
			{
				return laserVector[i];
			}
		}

		return NULL;
	}
	vector<Laser*> LaserPooling::getLaserVector()
	{
		return laserVector;
	}
	vector<Laser*> LaserPooling::getActiveLasers()
	{
		vector<Laser*> activeLasers = vector<Laser*>();

		for (int i = 0; i < laserVector.size(); i++)
		{
			if (laserVector[i]->getIsActive())
			{
				activeLasers.push_back(laserVector[i]);
			}
		}

		return activeLasers;
	}
}
