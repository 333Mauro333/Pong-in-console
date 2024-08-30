#include "text.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Text::Text(int x, int y, string text, COLOR color, bool withFrame) : GameObject(x, y, text.length(), 1)
	{
		this->text = text;
		this->color = color;
		this->withFrame = withFrame;

		if (withFrame)
		{
			size.w += 4;
			size.h += 2;
		}
	}
	Text::~Text()
	{

	}


	void Text::draw()
	{
		int x = position.x + size.w / 2;
		int y = position.y;

		if (withFrame)
		{
			ConsoleExt::drawFrame(x, y, x + size.w - 1, y + 2, color);

			ConsoleExt::goToCoordinates(x + 2, y + 1);
		}
		else
		{
			ConsoleExt::goToCoordinates(x, y);
		}

		ConsoleExt::writeWithColor(text, color);
	}

	void Text::setColor(COLOR color)
	{
		this->color = color;
	}
}
