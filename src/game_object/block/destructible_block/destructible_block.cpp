#include "destructible_block.h"

#include "game_values/game_values.h"


namespace pong_in_console
{
	DestructibleBlock::DestructibleBlock(int x, int y, BLOCK_TYPE blockType) : Block(x, y, blockType)
	{
		pointsValue = GameValues::getBlockValue(blockType);
	}
	DestructibleBlock::~DestructibleBlock()
	{

	}


	int DestructibleBlock::getPointsValue()
	{
		return pointsValue;
	}
}
