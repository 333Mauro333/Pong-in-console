#ifndef LASER_POOLING_H
#define LASER_POOLING_H

#include <vector>

#include "game_object/laser/laser.h"

using std::vector;


namespace pong_in_console
{
	class LaserPooling
	{
	public:
		static LaserPooling* getInstance();

		LaserPooling(int amountOfLasers);
		~LaserPooling();

		Laser* getLaser();
		vector<Laser*> getLaserVector();
		vector<Laser*> getActiveLasers();

	private:
		static LaserPooling* instance;

		vector<Laser*> laserVector;
	};
}

#endif // !LASER_POOLING_H
