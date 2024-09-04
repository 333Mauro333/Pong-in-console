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
		//MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		player = new Paddle(30, 20);
		ball = new Ball(50, 15);
		frame = new Frame(ConsoleExt::getScreenWidth() / 2 - frameWidth / 2,
						  ConsoleExt::getScreenHeight() / 2 - frameHeight / 2,
						  frameWidth, frameHeight, COLOR::C_BWHITE);

		player->setMovementLimits(frame);
		ball->setMovementLimits(frame);
	}
	Gameplay::~Gameplay()
	{
		delete player;
		delete ball;
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

		if (CollisionManager::isColliding(player, ball))
		{
			ball->setCollisionDetection();
			ball->changeDirection(false, true);
		}
	}
	void Gameplay::erase()
	{
		ball->erase();
		player->erase();
	}
	void Gameplay::draw()
	{
		frame->draw();
		player->draw();
		ball->draw();
	}
}
