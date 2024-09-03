#include "gameplay.h"

#include "managers/collision_manager/collision_manager.h"
#include "managers/controls_manager/controls_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"


namespace pong_in_console
{
	Gameplay::Gameplay()
	{
		//MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		player = new Paddle(30, 5);
		ball = new Ball(20, 1);
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
		player->draw();
		ball->draw();
	}
}
