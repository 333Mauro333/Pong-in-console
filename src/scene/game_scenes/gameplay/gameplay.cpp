#include "gameplay.h"

#include <string>

#include "game_object/block/destructible_block/destructible_block.h"
#include "game_object/block/indestructible_block/indestructible_block.h"
#include "managers/collision_manager/collision_manager.h"
#include "managers/controls_manager/controls_manager.h"
#include "managers/file_manager/file_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Gameplay::Gameplay(int levelNumber)
	{
		string levelInfo = FileManager::loadLevel(levelNumber);
		const int frameWidth = 42;
		const int frameHeight = 24;
		int firstPositionX = 0;
		int firstPositionY = 0;
		int x = 0;
		int y = 0;


		player = new Paddle(60, 23);
		ball = new Ball(55, 8, BALL_DIRECTION::DOWN_LEFT);
		frame = new Frame(ConsoleExt::getScreenWidth() / 2 - frameWidth / 2,
						  ConsoleExt::getScreenHeight() / 2 - frameHeight / 2 + 2,
						  frameWidth, frameHeight, COLOR::C_BWHITE);
		
		blocks = vector<Block*>();

		firstPositionX = frame->getLeft() + 1;
		firstPositionY = frame->getUp() + 1;
		x = firstPositionX;
		y = firstPositionY;

		player->setMovementLimits(frame);
		ball->setMovementLimits(frame);

		for (int i = 0; i < levelInfo.size(); i++)
		{
			Block* blockToCreate = NULL;

			if (levelInfo[i] == '\n')
			{
				x = firstPositionX;
				y++;
				continue;
			}
			else if (levelInfo[i] == '1' || levelInfo[i] == '2' || levelInfo[i] == '3' || levelInfo[i] == '4')
			{
				int foundNumber = (int)levelInfo[i] - 48;

				blockToCreate = new DestructibleBlock(x, y, (BLOCK_TYPE)foundNumber);
				blocks.push_back(blockToCreate);
			}
			else if (levelInfo[i] == '0')
			{
				blockToCreate = new IndestructibleBlock(x, y);
			}

			x++;
		}
	}
	Gameplay::~Gameplay()
	{
		delete frame;
		delete player;
		delete ball;

		for (int i = 0; i < blocks.size(); i++)
		{
			delete blocks[i];
		}
	}


	void Gameplay::inputUpdate(int key)
	{
		player->inputUpdate(key);

		if (ControlsManager::isPressed(key, MENU_CONTROLS::BACK))
		{
			SceneManager::loadScene(SCENE_TO_LOAD::MAIN_MENU, COLOR::C_BLUE);
		}
	}
	void Gameplay::update()
	{
		ball->update();
		player->update();

		checkBallCollisions();
	}
	void Gameplay::erase()
	{
		ball->erase();
		player->erase();
	}
	void Gameplay::draw()
	{
		frame->draw();
		ball->draw();
		player->draw();

		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i]->draw();
		}
	}


	void Gameplay::checkBallCollisions()
	{
		CollisionManager::applyCollisionBetweenBallAndBlocks(ball, blocks);
		CollisionManager::applyCollisionBetweenBallAndPaddle(ball, player);
	}
}
