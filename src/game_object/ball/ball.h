#ifndef BALL_H
#define BALL_H

#include "mgtv_library.h"

#include "enums/ball_direction.h"
#include "game_object/frame/frame.h"
#include "game_object/game_object.h"
#include "interface_simulation/limited_element/limited_element.h"
#include "structs/limits.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Ball : public GameObject, public LimitedElement
	{
	public:
		Ball(int x, int y, BALL_DIRECTION ballDirection = BALL_DIRECTION::DOWN_RIGHT);
		~Ball();

		void update();
		void draw() override;

		void invertDirection(bool horizontal, bool vertical);

		BALL_DIRECTION getBallDirection();
		void setMovementLimits(Frame* frame) override;

		bool isTimeToDetectCollision();
		bool isItGoingDown();
		bool isItGoingRight();

	private:
		COLOR color;
		int delayToMove;
		int timer;
		
		int speedX;
		int speedY;

		LIMITS externalLimits;

		void applyMovement();

		bool canItGoUp();
		bool canItGoDown();
		bool canItGoLeft();
		bool canItGoRight();
	};
}

#endif // !BALL_H
