#ifndef FRAME_H
#define FRAME_H

#include "mgtv_library.h"

#include "game_object/game_object.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Frame : public GameObject
	{
	public:
		Frame(int x, int y, int w, int h, COLOR color);
		~Frame();

		void draw() override;

	private:
		COLOR color;
		bool itWasDrawn;
	};
}

#endif // !FRAME_H
