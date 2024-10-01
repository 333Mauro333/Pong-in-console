#include "block.h"

#include "game_values/game_values.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Block::Block(int x, int y, BLOCK_TYPE blockType) : GameObject(x, y, 1, 1)
	{
		picture = GameValues::getBlockPicture(blockType);
		this->blockType = blockType;
		isTheFirstFrame = true;
	}
	Block::~Block()
	{
		
	}

	void Block::draw()
	{
		if (isTheFirstFrame)
		{
			isTheFirstFrame = false;
			ConsoleExt::goToCoordinates(position.x, position.y);
			ConsoleExt::writeWithColor(picture.picture, picture.color);
		}
	}

	BLOCK_TYPE Block::getBlockType()
	{
		return blockType;
	}
}
