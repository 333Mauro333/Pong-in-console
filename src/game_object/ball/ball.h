#ifndef BALL_H
#define BALL_H

#include "mgtv_library.h"

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
		Ball(int x, int y);
		~Ball();

		void update();
		void draw() override;

		void changeDirection(bool horizontal, bool vertical);

		void setCollisionDetection();
		void setMovementLimits(Frame* frame) override;

		bool isCollisionDetected();
		bool isTimeToDetectCollision();
		bool isItGoingDown();
		bool isItGoingRight();

	private:
		COLOR color;
		int delayToMove;
		int timer;

		bool detectedCollision;
		
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
