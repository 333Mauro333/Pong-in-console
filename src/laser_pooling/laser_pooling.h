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
		static void initLasers();
		static void updateLasers();
		static void eraseLasers();
		static void drawLasers();
		static void destroyLasers();

		static Laser* getLaser();
		static vector<Laser*> getActiveLasers();
		static void setLasersLimits(Frame* frame);

	private:
		static const int amountOfLasers = 4;
		static Laser* lasers[amountOfLasers];
	};
}

#endif // !LASER_POOLING_H
