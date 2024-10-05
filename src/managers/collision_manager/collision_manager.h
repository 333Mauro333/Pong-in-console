#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

#include "enums/ball_direction.h"
#include "enums/direction.h"
#include "enums/side.h"
#include "game_object/ball/ball.h"
#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/bullet/bullet.h"
#include "game_object/paddle/paddle.h"

using std::vector;


namespace pong_in_console
{
	class CollisionManager
	{
	public:
		static bool applyCollisionBetweenBallAndBlocks(Ball* ball, vector<Block*> blocks, int& actualPoints);
		static void applyCollisionBetweenBallAndPaddle(Ball* ball, Paddle* paddle);
		static void applyCollisionBetweenBallAndBullet(Ball* ball, Bullet* bullet);
		static bool applyCollisionBetweenLasersAndBlocks(vector<Laser*> activeLasers, vector<Block*> blocks, int& actualPoints);

	private:
		static vector<Block*> getCollidedBlocks(Ball* ball, vector<Block*> blocks);
		static bool ballIsGoingInThatDirection(Ball* ball, BALL_DIRECTION direction);
		static bool isTheBlockInBallSRange(Ball* ball, Block* block);
		static bool thereAreBlocks(vector<Block*> vectorBlock, int searchedAmount);
		static bool makeTheBallAndOneBlockReact(Ball* ball, Block* block, int& actualPoints);
		static bool makeTheBallAndTwoBlocksReact(Ball* ball, vector<Block*> blocks, int& actualPoints);
		static bool makeTheBallAndThreeBlocksReact(Ball* ball, vector<Block*> blocks, int& actualPoints);
		static bool makeTheBallAndFourBlocksReact(Ball* ball, vector<Block*> blocks, int& actualPoints);
		static bool makeTheBallAndFiveBlocksReact(Ball* ball, vector<Block*> blocks, int& actualPoints);
		static bool isTheBallAdjacentToOneBlock(Ball* ball, Block* block, DIRECTION searchedDirection);
		static bool isTheBallAdjacentToMultipleBlocks(Ball* ball, vector<Block*> blocks, vector<DIRECTION> searchedDirections);

		static bool isTheBallInsideThePaddle(Ball* ball, Paddle* paddle, SIDE cornerSide);
		static void setReactionOfTheBallByThePaddle(Ball* ball, Paddle* paddle, BALL_DIRECTION finalBallDirection);
		static bool ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction);
		static bool isTheBallOverThePaddle(Paddle* paddle, Ball* ball);
		static void reactBallAndBlock(Ball* ball, Block* block, bool invertHorizontal, bool invertVertical);
		static void reactAllBlocks(vector<Block*> blocks);

		static bool thePositionIsTheSame(Ball* ball, Bullet* bullet);
		static void addPointsIfItIsADestructibleBlock(Block* block, int& actualPoints);
		static void addPointsIfTheyAreDestructibleBlocks(vector<Block*> blocks, int& actualPoints);

		static bool thePositionIsTheSame(Laser* laser, Block* block);
	};
}

#endif // !COLLISION_MANAGER_H
