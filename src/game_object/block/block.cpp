#include "block.h"

#include "game_values/game_values.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Block::Block(int x, int y, BLOCK_TYPE blockType) : GameObject(x, y, 1, 1)
	{
		picture = GameValues::getBlockPicture(blockType);
		this->blockType = blockType;
		itWasDrawn = false;
	}
	Block::~Block()
	{
		
	}

	void Block::draw()
	{
		if (!itWasDrawn)
		{
			itWasDrawn = true;
			ConsoleExt::goToCoordinates(position.x, position.y);
			ConsoleExt::writeWithColor(picture.picture, picture.color);
		}
	}

	void Block::setItWasDrawn(bool itWasDrawn)
	{
		this->itWasDrawn = itWasDrawn;
	}

	BLOCK_TYPE Block::getBlockType()
	{
		return blockType;
	}
}
