#ifndef BALL_H
#define BALL_H

#include "mgtv_library.h"

#include "game_object/game_object.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Ball : public GameObject
	{
	public:
		Ball(int x, int y);
		~Ball();

		void update();
		void draw() override;

		void changeDirection(bool horizontal, bool vertical);
		void setCollisionDetection();

		bool isCollisionDetected();
		bool isTimeToDetectCollision();
		bool isItGoingDown();

	private:
		COLOR color;
		int delayToMove;
		int timer;

		int speedX;
		int speedY;

		bool detectedCollision;
	};
}

#endif // !BALL_H
