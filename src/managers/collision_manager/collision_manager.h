#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

#include "enums/ball_collision_type.h"
#include "enums/direction.h"
#include "enums/side.h"
#include "game_object/ball/ball.h"
#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/paddle/paddle.h"

using std::vector;


namespace pong_in_console
{
	class CollisionManager
	{
	public:
		static BALL_COLLISION_TYPE getBallCollisionType(Paddle* paddle, Ball* ball);
		static void applyCollisionBetweenBallAndBlocks(Ball* ball, Block* blocks[], int blocksAmount);

	private:
		static bool isTheBallInPaddleRange(Paddle* paddle, Ball* ball);
		static bool ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction);
		static bool isTheBallOverThePaddle(Paddle* paddle, Ball* ball);

		static bool isTheBallAdjacentToTheBlock(Ball* ball, Block* block, DIRECTION directionToKnow);
		static bool isThereBlocks(vector<Block*> vectorBlock, int searchedAmount);
		static bool isDestructible(Block* block);
	};
}

#endif // !COLLISION_MANAGER_H
