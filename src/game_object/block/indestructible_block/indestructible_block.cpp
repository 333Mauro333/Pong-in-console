#include "indestructible_block.h"


namespace pong_in_console
{
	IndestructibleBlock::IndestructibleBlock(int x, int y) : Block(x, y, BLOCK_TYPE::B_INDESTRUCTIBLE)
	{

	}
	IndestructibleBlock::~IndestructibleBlock()
	{

	}


	void IndestructibleBlock::reactToTheBall()
	{
		// Play metal sound.
	}
}
