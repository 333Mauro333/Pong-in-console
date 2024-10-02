#ifndef LASER_H
#define LASER_H

#include "mgtv_library.h"

#include "game_object/game_object.h"
#include "interface_simulation/limited_element/limited_element.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Laser : public GameObject, public LimitedElement
	{
	public:
		Laser();
		~Laser();

		void update();
		void draw() override;

		void impact();

		void setMovementLimits(Frame* frame) override;

	private:
		COLOR color;
		int delayToMove;
		int counter;

		int yLimit;

		bool isTimeToMove();
		void resetCounter();
		void moveUp();
		void moveDown();
		bool itReachedTheLimit();
		void discountCounter();

		bool movedInThisFrame();
		void drawLaser();
	};
}

#endif // !LASER_H
