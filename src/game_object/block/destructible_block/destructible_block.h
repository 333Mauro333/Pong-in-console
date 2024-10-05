#ifndef DESTRUCTIBLE_BLOCK_H
#define DESTRUCTIBLE_BLOCK_H

#include "game_object/block/block.h"


namespace pong_in_console
{
	class DestructibleBlock : public Block
	{
	public:
		DestructibleBlock(int x, int y, BLOCK_TYPE blockType);
		~DestructibleBlock();

		void reactToTheBall() override;

		int getPointsValue();

	private:
		int pointsValue;
	};
}

#endif // !DESTRUCTIBLE_BLOCK_H
