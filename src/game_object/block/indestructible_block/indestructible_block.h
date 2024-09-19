#ifndef INDESTRUCTIBLE_BLOCK_H
#define INDESTRUCTIBLE_BLOCK_H

#include "game_object/block/block.h"


namespace pong_in_console
{
	class IndestructibleBlock : public Block
	{
	public:
		IndestructibleBlock(int x, int y);
		~IndestructibleBlock();

		void reactToTheBall() override;
	};
}

#endif // !INDESTRUCTIBLE_BLOCK_H
