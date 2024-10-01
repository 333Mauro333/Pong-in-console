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
		Ball(int x, int y, BALL_DIRECTION ballDirection);
		~Ball();

		void update();
		void draw() override;

		void redirectInLimits();
		void invertDirection(bool horizontal, bool vertical);

		BALL_DIRECTION getBallDirection();
		void setDirection(BALL_DIRECTION ballDirection);
		void setPosition(int x, int y) override;
		void setMovementLimits(Frame* frame) override;

		bool isTimeToDetectCollision();
		bool isGoingDown();
		bool isGoingRight();
		bool canGoUp();
		bool canGoDown();
		bool canGoLeft();
		bool canGoRight();

	private:
		COLOR color;
		int delayToMove;
		int counter;
		bool isTheFirstFrame;
		
		int speedX;
		int speedY;

		LIMITS externalLimits;

		bool isTimeToMove();
		bool movedInThisFrame();
		void resetCounter();
		void discountCounter();

		void applyMovement();
	};
}

#endif // !BALL_H
