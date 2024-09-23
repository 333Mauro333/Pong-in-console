#include "frame.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Frame::Frame(int x, int y, int w, int h, COLOR color) : GameObject(x, y, w, h)
	{
		this->color = color;
		itWasDrawn = false;
	}
	Frame::~Frame()
	{

	}


	void Frame::draw()
	{
		if (!itWasDrawn)
		{
			itWasDrawn = true;

			ConsoleExt::drawFrame(position.x, position.y,
								  position.x + size.w - 1, position.y + size.h - 1,
								  color);
		}
	}
}
