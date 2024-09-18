#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "structs/position.h"
#include "structs/size.h"


namespace pong_in_console
{
	class GameObject
	{
	public:
		GameObject(int x, int y);
		GameObject(int x, int y, int w, int h);
		virtual ~GameObject();

		void erase();
		virtual void draw() = 0;

		void activate();
		void deactivate();

		bool getIsActive();
		POSITION getPosition();
		SIZE getSize();
		int getUp();
		int getDown();
		int getLeft();
		int getRight();

		virtual void setPosition(POSITION position);
		virtual void setPosition(int x, int y);
		void setSize(SIZE position);
		void setSize(int w, int h);

	protected:
		bool isActive;
		POSITION position;
		SIZE size;

		void savePositionAsPrevious();

	private:
		POSITION previousPosition;
	};
}

#endif // !GAME_OBJECT_H
