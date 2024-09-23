﻿#include "collision_manager.h"


namespace pong_in_console
{
	void CollisionManager::applyCollisionBetweenBallAndBlocks(Ball* ball, vector<Block*> blocks)
	{
		if (ball->isTimeToDetectCollision())
		{
			vector<Block*> collidedBlocksVector = vector<Block*>();

			collidedBlocksVector = getCollidedBlocks(ball, blocks);

			if (thereAreBlocks(collidedBlocksVector, 1))
			{
				Block* collidedBlock = collidedBlocksVector[0];

				makeTheBallAndOneBlockReact(ball, collidedBlock);
			}
			else if (thereAreBlocks(collidedBlocksVector, 2))
			{
				makeTheBallAndTwoBlocksReact(ball, collidedBlocksVector);
			}
			else if (thereAreBlocks(collidedBlocksVector, 3))
			{
				makeTheBallAndThreeBlocksReact(ball, collidedBlocksVector);
			}
			else if (thereAreBlocks(collidedBlocksVector, 4))
			{
				makeTheBallAndFourBlocksReact(ball, collidedBlocksVector);
			}
			else if (thereAreBlocks(collidedBlocksVector, 5))
			{
				makeTheBallAndFiveBlocksReact(ball, collidedBlocksVector);
			}
		}
	}
	void CollisionManager::applyCollisionBetweenBallAndPaddle(Ball* ball, Paddle* paddle)
	{
		if (paddle->movedInThisFrame(SIDE::LEFT) &&
			isTheBallInsideThePaddle(ball, paddle, SIDE::LEFT))
		{
			setReactionOfTheBallByThePaddle(ball, paddle, BALL_DIRECTION::UP_LEFT);
		}
		else if (paddle->movedInThisFrame(SIDE::RIGHT) &&
				 isTheBallInsideThePaddle(ball, paddle, SIDE::RIGHT))
		{
			setReactionOfTheBallByThePaddle(ball, paddle, BALL_DIRECTION::UP_RIGHT);
		}

		if (ball->isTimeToDetectCollision() && ball->isGoingDown())
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
	}
	void CollisionManager::applyCollisionBetweenBallAndBullet(Ball* ball, Bullet* bullet)
	{
		if (bullet->getIsActive() && thePositionIsTheSame(ball, bullet))
		{
			if (ball->isGoingDown())
			{
				ball->invertDirection(false, true);
			}
			else
			{
				ball->move(0, -1);
			}

			bullet->impact();
		}
	}


	vector<Block*> CollisionManager::getCollidedBlocks(Ball* ball, vector<Block*> levelBlocks)
	{
		vector<Block*> detectedBlocks = vector<Block*>();

		for (int i = 0; i < levelBlocks.size(); i++)
		{
			if (levelBlocks[i]->getIsActive() && isTheBlockInBallSRange(ball, levelBlocks[i]))
			{
				detectedBlocks.push_back(levelBlocks[i]);
			}
		}

		return detectedBlocks;
	}
	bool CollisionManager::ballIsGoingInThatDirection(Ball* ball, BALL_DIRECTION direction)
	{
		return ball->getBallDirection() == direction;
	}
	bool CollisionManager::isTheBlockInBallSRange(Ball* ball, Block* block)
	{
		return block->getPosition().x >= ball->getPosition().x - 1 &&
			   block->getPosition().x <= ball->getPosition().x + 1 &&
			   block->getPosition().y >= ball->getPosition().y - 1 &&
			   block->getPosition().y <= ball->getPosition().y + 1;
	}
	bool CollisionManager::thereAreBlocks(vector<Block*> vectorBlock, int searchedAmount)
	{
		return vectorBlock.size() == searchedAmount;
	}
	void CollisionManager::makeTheBallAndOneBlockReact(Ball* ball, Block* block)
	{
		if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::UPPER_CENTER))
			{
				reactBallAndBlock(ball, block, false, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::UPPER_RIGHT))
			{
				bool invertHorizontal = true;

				if (!ball->canGoLeft())
				{
					invertHorizontal = false;
				}

				reactBallAndBlock(ball, block, invertHorizontal, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::MIDDLE_RIGHT))
			{
				reactBallAndBlock(ball, block, true, false);
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::UPPER_CENTER))
			{
				reactBallAndBlock(ball, block, false, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::UPPER_LEFT))
			{
				bool invertHorizontal = true;

				if (!ball->canGoRight())
				{
					invertHorizontal = false;
				}

				reactBallAndBlock(ball, block, invertHorizontal, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::MIDDLE_LEFT))
			{
				reactBallAndBlock(ball, block, true, false);
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::LOWER_CENTER))
			{
				reactBallAndBlock(ball, block, false, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::LOWER_RIGHT))
			{
				bool invertHorizontal = true;
				bool invertVertical = true;

				if (!ball->canGoLeft())
				{
					invertHorizontal = false;
				}

				if (!ball->canGoUp())
				{
					invertVertical = false;
				}

				reactBallAndBlock(ball, block, invertHorizontal, invertVertical);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::MIDDLE_RIGHT))
			{
				reactBallAndBlock(ball, block, true, false);
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::LOWER_CENTER))
			{
				reactBallAndBlock(ball, block, false, true);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::LOWER_LEFT))
			{
				bool invertHorizontal = true;
				bool invertVertical = true;

				if (!ball->canGoRight())
				{
					invertHorizontal = false;
				}

				if (!ball->canGoUp())
				{
					invertVertical = false;
				}

				reactBallAndBlock(ball, block, invertHorizontal, invertVertical);
			}
			else if (isTheBallAdjacentToOneBlock(ball, block, DIRECTION::MIDDLE_LEFT))
			{
				reactBallAndBlock(ball, block, true, false);
			}
		}
	}
	void CollisionManager::makeTheBallAndTwoBlocksReact(Ball* ball, vector<Block*> blocks)
	{
		if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[0]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[0]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[0]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[0]->reactToTheBall();
			}
		}
	}
	void CollisionManager::makeTheBallAndThreeBlocksReact(Ball* ball, vector<Block*> blocks)
	{
		if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, false);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				reactAllBlocks(blocks);
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(false, true);
				blocks[1]->reactToTheBall();
			}
		}
	}
	void CollisionManager::makeTheBallAndFourBlocksReact(Ball* ball, vector<Block*> blocks)
	{
		if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
			else if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
			}
		}
	}
	void CollisionManager::makeTheBallAndFiveBlocksReact(Ball* ball, vector<Block*> blocks)
	{
		if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::UP_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::UPPER_CENTER, DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT }))
			{
				ball->invertDirection(true, true);
				blocks[0]->reactToTheBall();
				blocks[1]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_RIGHT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_RIGHT, DIRECTION::MIDDLE_RIGHT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[3]->reactToTheBall();
				blocks[4]->reactToTheBall();
			}
		}
		else if (ballIsGoingInThatDirection(ball, BALL_DIRECTION::DOWN_LEFT))
		{
			if (isTheBallAdjacentToMultipleBlocks(ball, blocks, { DIRECTION::UPPER_LEFT, DIRECTION::MIDDLE_LEFT, DIRECTION::LOWER_LEFT, DIRECTION::LOWER_CENTER, DIRECTION::LOWER_RIGHT }))
			{
				ball->invertDirection(true, true);
				blocks[1]->reactToTheBall();
				blocks[2]->reactToTheBall();
				blocks[3]->reactToTheBall();
			}
		}
	}

	bool CollisionManager::isTheBallAdjacentToOneBlock(Ball* ball, Block* block, DIRECTION searchedDirection)
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
	bool CollisionManager::isTheBallAdjacentToMultipleBlocks(Ball* ball, vector<Block*> blocks, vector<DIRECTION> searchedDirections)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			if (!isTheBallAdjacentToOneBlock(ball, blocks[i], searchedDirections[i]))
			{
				return false;
			}
		}

		return true;
	}

	bool CollisionManager::isTheBallInsideThePaddle(Ball* ball, Paddle* paddle, SIDE cornerSide)
	{
		switch (cornerSide)
		{
		case SIDE::LEFT:
			return ball->getPosition().x == paddle->getLeft() && ball->getPosition().y == paddle->getUp();

		case SIDE::RIGHT:
			return ball->getPosition().x == paddle->getRight() && ball->getPosition().y == paddle->getUp();

		default:
			return false;
		}
	}
	void CollisionManager::setReactionOfTheBallByThePaddle(Ball* ball, Paddle* paddle, BALL_DIRECTION finalBallDirection)
	{
		ball->setDirection(finalBallDirection);

		switch (finalBallDirection)
		{
		case BALL_DIRECTION::UP_LEFT:
			ball->setPosition(paddle->getLeft() - 1, paddle->getUp() - 1);
			break;

		case BALL_DIRECTION::UP_RIGHT:
			ball->setPosition(paddle->getRight() + 1, paddle->getUp() - 1);
			break;
		}
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
			return ball->isGoingRight() &&
				   ballX == paddleLeft - 1 && ballY == paddleY - 1;

		case SIDE::RIGHT:
			return !ball->isGoingRight() &&
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
	void CollisionManager::reactBallAndBlock(Ball* ball, Block* block, bool invertHorizontal, bool invertVertical)
	{
		ball->invertDirection(invertHorizontal, invertVertical);
		block->reactToTheBall();
	}
	void CollisionManager::reactAllBlocks(vector<Block*> blocks)
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			if (blocks[i]->getBlockType() != BLOCK_TYPE::B_INDESTRUCTIBLE)
			{
				blocks[i]->deactivate();
			}
		}
	}

	bool CollisionManager::thePositionIsTheSame(Ball* ball, Bullet* bullet)
	{
		return ball->getPosition().x == bullet->getPosition().x &&
			   ball->getPosition().y == bullet->getPosition().y;
	}
}
