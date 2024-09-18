#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

#include "enums/ball_direction.h"
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
		static void applyCollisionBetweenBallAndBlocks(Ball* ball, Block* blocks[], int blocksAmount);
		static void applyCollisionBetweenBallAndPaddle(Ball* ball, Paddle* paddle);

	private:
		static vector<Block*> getCollidedBlocks(Ball* ball, Block* levelBlocks[], int blocksAmount);
		static bool isTheBallGoingInThatDirection(Ball* ball, BALL_DIRECTION direction);
		static bool isTheBlockInBallSRange(Ball* ball, Block* block, SIDE side);
		static bool isThereBlocks(vector<Block*> vectorBlock, int searchedAmount);
		static void makeTheBallAndOneBlockReact(Ball* ball, Block* block);
		static bool isTheBallAdjacentToTheBlock(Ball* ball, Block* block, DIRECTION searchedDirection);
		static bool isDestructible(Block* block);

		static bool isTheBallInsideThePaddle(Ball* ball, Paddle* paddle, SIDE cornerSide);
		static void setReactionOfTheBallByThePaddle(Ball* ball, Paddle* paddle, BALL_DIRECTION finalBallDirection);
		static bool ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction);
		static bool isTheBallOverThePaddle(Paddle* paddle, Ball* ball);
	};
}

#endif // !COLLISION_MANAGER_H
