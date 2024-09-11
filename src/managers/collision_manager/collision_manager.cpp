#include "collision_manager.h"


namespace pong_in_console
{
	BALL_COLLISION_TYPE CollisionManager::getBallCollisionType(Paddle* paddle, Ball* ball)
	{
		if (isTheBallInPaddleRange(paddle, ball))
		{
			if (ballCollidesInPaddleCorner(paddle, ball, SIDE::LEFT))
			{
				return BALL_COLLISION_TYPE::PAD_CORNER_LEFT;
			}
			else if (ballCollidesInPaddleCorner(paddle, ball, SIDE::RIGHT))
			{
				return BALL_COLLISION_TYPE::PAD_CORNER_RIGHT;
			}
			else if (isTheBallOverThePaddle(paddle, ball))
			{
				return BALL_COLLISION_TYPE::PAD_SURFACE;
			}
		}

		return BALL_COLLISION_TYPE::NONE;
	}
	void CollisionManager::applyCollisionBetweenBallAndBlocks(Ball* ball, Block* blocks[], int blocksAmount)
	{
		if (ball->isTimeToDetectCollision() && ball->getBallDirection() == BALL_DIRECTION::UP_RIGHT)
		{
			vector<Block*> blocksVector = vector<Block*>();
			vector<DIRECTION> directionsVector = vector<DIRECTION>();
			const int directionsAmount = 9;

			for (int i = 0; i < blocksAmount; i++)
			{
				if (blocks[i]->getPosition().x >= ball->getPosition().x - 1 &&
					blocks[i]->getPosition().x <= ball->getPosition().x + 1 &&
					blocks[i]->getPosition().y >= ball->getPosition().y - 1 &&
					blocks[i]->getPosition().y <= ball->getPosition().y)
				{
					blocksVector.push_back(blocks[i]);
				}
			}

			if (isThereBlocks(blocksVector, 1))
			{
				Block* collidedBlock = blocksVector[0];

				if (isTheBallAdjacentToTheBlock(ball, collidedBlock, DIRECTION::CENTER_TOP))
				{
					ball->invertDirection(false, true);
				}
				else if (isTheBallAdjacentToTheBlock(ball, collidedBlock, DIRECTION::RIGHT_TOP))
				{
					ball->invertDirection(true, true);
				}
				else if (isTheBallAdjacentToTheBlock(ball, collidedBlock, DIRECTION::RIGHT_MIDDLE))
				{
					ball->invertDirection(true, false);
				}

				if (isDestructible(collidedBlock))
				{
					collidedBlock->deactivate();
				}
			}
		}
	}

	bool CollisionManager::isTheBallInPaddleRange(Paddle* paddle, Ball* ball)
	{
		return ball->isItGoingDown() && ball->isTimeToDetectCollision() &&
			   ball->getIsActive() && paddle->getIsActive() &&
			   ball->getPosition().y == paddle->getPosition().y - 1 &&
			   ball->getPosition().x >= paddle->getLeft() - 1 &&
			   ball->getPosition().x <= paddle->getRight() + 1;
	}
	bool CollisionManager::ballCollidesInPaddleCorner(Paddle* paddle, Ball* ball, SIDE direction)
	{
		switch (direction)
		{
		case SIDE::LEFT:
			return ball->getPosition().x == paddle->getLeft() - 1 &&
				   ball->isItGoingRight();

		case SIDE::RIGHT:
		default:
			return ball->getPosition().x == paddle->getRight() + 1 &&
				   !ball->isItGoingRight();
		}
	}
	bool CollisionManager::isTheBallOverThePaddle(Paddle* paddle, Ball* ball)
	{
		return ball->getPosition().x >= paddle->getLeft() &&
			   ball->getPosition().x <= paddle->getRight();
	}

	bool CollisionManager::isTheBallAdjacentToTheBlock(Ball* ball, Block* block, DIRECTION directionToKnow)
	{
		switch (directionToKnow)
		{
		case DIRECTION::LEFT_TOP:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::CENTER_TOP:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::RIGHT_TOP:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y - 1;

		case DIRECTION::LEFT_MIDDLE:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::CENTER_MIDDLE:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::RIGHT_MIDDLE:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y;

		case DIRECTION::LEFT_BOT:
			return block->getPosition().x == ball->getPosition().x - 1 &&
				   block->getPosition().y == ball->getPosition().y + 1;

		case DIRECTION::CENTER_BOT:
			return block->getPosition().x == ball->getPosition().x &&
				   block->getPosition().y == ball->getPosition().y + 1;

		case DIRECTION::RIGHT_BOT:
			return block->getPosition().x == ball->getPosition().x + 1 &&
				   block->getPosition().y == ball->getPosition().y + 1;

		default:
			return false;
		}
	}
	bool CollisionManager::isThereBlocks(vector<Block*> vectorBlock, int searchedAmount)
	{
		return vectorBlock.size() == searchedAmount;
	}
	bool CollisionManager::isDestructible(Block* block)
	{
		return block->getBlockType() != BLOCK_TYPE::B_INDESTRUCTIBLE;
	}
}
