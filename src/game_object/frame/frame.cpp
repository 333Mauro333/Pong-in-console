#include "frame.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Frame::Frame(int x, int y, int w, int h, COLOR color) : GameObject(x, y, w, h)
	{
		this->color = color;
		wasItDrawn = false;
	}
	Frame::~Frame()
	{

	}


	void Frame::draw()
	{
		if (!wasItDrawn)
		{
			wasItDrawn = true;

			ConsoleExt::drawFrame(position.x, position.y,
								  position.x + size.w - 1, position.y + size.h - 1,
								  color);
		}
	}

	int Frame::getUp()
	{
		return position.y;
	}
	int Frame::getDown()
	{
		return position.y + size.h - 1;
	}
	int Frame::getLeft()
	{
		return position.x;
	}
	int Frame::getRight()
	{
		return position.x + size.w - 1;
	}
}
