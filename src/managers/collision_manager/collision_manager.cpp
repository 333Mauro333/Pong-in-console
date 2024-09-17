#include "collision_manager.h"


namespace pong_in_console
{
	void CollisionManager::applyCollisionBetweenBallAndBlocks(Ball* ball, Block* blocks[], int blocksAmount)
	{
		if (ball->isTimeToDetectCollision())
		{
			vector<Block*> collidedBlocksVector = vector<Block*>();

			collidedBlocksVector = getCollidedBlocks(ball, blocks, blocksAmount);

			if (isThereBlocks(collidedBlocksVector, 1))
			{
				Block* collidedBlock = collidedBlocksVector[0];

				makeTheBallAndOneBlockReact(ball, collidedBlock);

				if (isDestructible(collidedBlock))
				{
					collidedBlock->deactivate();
				}
			}
		}
	}
	void CollisionManager::applyCollisionBetweenBallAndPaddle(Ball* ball, Paddle* paddle)
	{
		if (ballCollidesInPaddleCorner(paddle, ball, SIDE::LEFT) ||
			ballCollidesInPaddleCorner(paddle, ball, SIDE::RIGHT))
		{
			ball->invertDirection(true, true);
		}
		else if (isTheBallOverThePaddle(paddle, ball))
		{
			ball->invertDirection(false, true);
		}
	}

	vector<Block*> CollisionManager::getCollidedBlocks(Ball* ball, Block* levelBlocks[], int blocksAmount)
	{
		vector<Block*> detectedBlocks = vector<Block*>();
		SIDE sideToRevise = SIDE::UP;

		if (isTheBallGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT) ||
			isTheBallGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			sideToRevise = SIDE::DOWN;
		}

		for (int i = 0; i < blocksAmount; i++)
		{
			if (isTheBlockInBallSRange(ball, levelBlocks[i], sideToRevise))
			{
				detectedBlocks.push_back(levelBlocks[i]);
			}
		}

		return detectedBlocks;
	}
	bool CollisionManager::isTheBallGoingInThatDirection(Ball* ball, BALL_DIRECTION direction)
	{
		return ball->getBallDirection() == direction;
	}
	bool CollisionManager::isTheBlockInBallSRange(Ball* ball, Block* block, SIDE side)
	{
		switch (side)
		{
		case SIDE::UP:
			return block->getPosition().x >= ball->getPosition().x - 1 &&
				   block->getPosition().x <= ball->getPosition().x + 1 &&
				   block->getPosition().y >= ball->getPosition().y - 1 &&
				   block->getPosition().y <= ball->getPosition().y;

		case SIDE::DOWN:
			return block->getPosition().x >= ball->getPosition().x - 1 &&
				   block->getPosition().x <= ball->getPosition().x + 1 &&
				   block->getPosition().y >= ball->getPosition().y &&
				   block->getPosition().y <= ball->getPosition().y + 1;

		default:
			return false;
		}
	}
	bool CollisionManager::isThereBlocks(vector<Block*> vectorBlock, int searchedAmount)
	{
		return vectorBlock.size() == searchedAmount;
	}
	void CollisionManager::makeTheBallAndOneBlockReact(Ball* ball, Block* block)
	{
		if (isTheBallGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::UPPER_CENTER))
			{
				ball->invertDirection(false, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::UPPER_RIGHT))
			{
				ball->invertDirection(true, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::MIDDLE_RIGHT))
			{
				ball->invertDirection(true, false);
			}
		}
		else if (isTheBallGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::UPPER_CENTER))
			{
				ball->invertDirection(false, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::UPPER_LEFT))
			{
				ball->invertDirection(true, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::MIDDLE_LEFT))
			{
				ball->invertDirection(true, false);
			}
		}
		else if (isTheBallGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::LOWER_CENTER))
			{
				ball->invertDirection(false, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::LOWER_RIGHT))
			{
				ball->invertDirection(true, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::MIDDLE_RIGHT))
			{
				ball->invertDirection(true, false);
			}
		}
		else if (isTheBallGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::LOWER_CENTER))
			{
				ball->invertDirection(false, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::LOWER_LEFT))
			{
				ball->invertDirection(true, true);
			}
			else if (isTheBallAdjacentToTheBlock(ball, block, DIRECTION::MIDDLE_LEFT))
			{
				ball->invertDirection(true, false);
			}
		}
	}
	bool CollisionManager::isTheBallAdjacentToTheBlock(Ball* ball, Block* block, DIRECTION searchedDirection)
	{
		switch (searchedDirection)
		{
		case DIRECTION::UPPER_LEFT:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::UPPER_CENTER:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::UPPER_RIGHT:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::MIDDLE_LEFT:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::MIDDLE_CENTER:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::MIDDLE_RIGHT:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::LOWER_LEFT:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y + 1;

		case DIRECTION::LOWER_CENTER:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y + 1;

		case DIRECTION::LOWER_RIGHT:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y + 1;

		default:
			return false;
		}
	}
	bool CollisionManager::isDestructible(Block* block)
	{
		return block->getBlockType() != BLOCK_TYPE::B_INDESTRUCTIBLE;
	}

	bool CollisionManager::isTheBallInPaddleRange(Paddle* paddle, Ball* ball)
	{
		return ball->isTimeToDetectCollision() && ball->isItGoingDown() &&
			   ball->getIsActive() && paddle->getIsActive() &&
			   ball->getPosition().y == paddle->getPosition().y - 1 &&
			   ball->getPosition().x >= paddle->getLeft() - 1 &&
			   ball->getPosition().x <= paddle->getRight() + 1;
	}
	bool CollisionManager::ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction)
	{
		int paddleLeft = paddle->getLeft();
		int paddleRight = paddle->getRight();
		int paddleY = paddle->getPosition().y;

		int ballX = ball->getPosition().x;
		int ballY = ball->getPosition().y;


		switch (direction)
		{
		case SIDE::LEFT:
			return ball->isItGoingRight() &&
				   ballX == paddleLeft - 1 && ballY == paddleY - 1;

		case SIDE::RIGHT:
			return !ball->isItGoingRight() &&
				   ballX == paddleRight + 1 && ballY == paddleY - 1;

		default:
			return false;
		}
	}
	bool CollisionManager::isTheBallOverThePaddle(Paddle* paddle, Ball* ball)
	{
		int paddleLeft = paddle->getLeft();
		int paddleRight = paddle->getRight();
		int paddleY = paddle->getPosition().y;

		int ballX = ball->getPosition().x;
		int ballY = ball->getPosition().y;


		return ballY == paddleY - 1 &&
			   ballX >= paddleLeft &&
			   ballX <= paddleRight;
	}
}
