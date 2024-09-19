#include "gameplay.h"

#include "managers/collision_manager/collision_manager.h"
#include "managers/controls_manager/controls_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Gameplay::Gameplay()
	{
		const int frameWidth = 80;
		const int frameHeight = 20;


		player = new Paddle(85, 20);
		ball = new Ball(55, 8, BALL_DIRECTION::DOWN_LEFT);
		frame = new Frame(ConsoleExt::getScreenWidth() / 2 - frameWidth / 2,
						  ConsoleExt::getScreenHeight() / 2 - frameHeight / 2,
						  frameWidth, frameHeight, COLOR::C_BWHITE);
		
		blocks[0] = new DestructibleBlock(50, 11, BLOCK_TYPE::B_GREEN);
		blocks[1] = new DestructibleBlock(50, 12, BLOCK_TYPE::B_GREEN);
		blocks[2] = new DestructibleBlock(50, 13, BLOCK_TYPE::B_GREEN);
		blocks[3] = new DestructibleBlock(51, 13, BLOCK_TYPE::B_GREEN);
		blocks[4] = new DestructibleBlock(52, 13, BLOCK_TYPE::B_GREEN);

		player->setMovementLimits(frame);
		ball->setMovementLimits(frame);
	}
	Gameplay::~Gameplay()
	{
		delete frame;
		delete player;
		delete ball;

		for (int i = 0; i < blocksAmount; i++)
		{
			delete blocks[i];
		}
	}


	void Gameplay::inputUpdate(int key)
	{
		player->inputUpdate(key);

		if (ControlsManager::isPressed(key, MENU_CONTROLS::BACK))
		{
			SceneManager::loadScene(SCENE_TO_LOAD::MAIN_MENU);
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

		for (int i = 0; i < blocksAmount; i++)
		{
			blocks[i]->draw();
		}
	}


	void Gameplay::checkBallCollisions()
	{
		CollisionManager::applyCollisionBetweenBallAndBlocks(ball, blocks, blocksAmount);
		CollisionManager::applyCollisionBetweenBallAndPaddle(ball, player);
	}
}
