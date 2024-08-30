#include "gameplay.h"

#include "managers/controls_manager/controls_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"


namespace pong_in_console
{
	Gameplay::Gameplay()
	{
		//MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		player = new Paddle(30, 10);
		ball = new Ball(20, 8);
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
