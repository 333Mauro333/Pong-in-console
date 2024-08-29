#include "gameplay.h"

#include "managers/music_manager/music_manager.h"


namespace pong_in_console
{
	Gameplay::Gameplay()
	{
		MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		player = new Paddle(30, 10);
	}
	Gameplay::~Gameplay()
	{
		delete player;
	}

	void Gameplay::inputUpdate(int key)
	{
		player->inputUpdate(key);
	}
	void Gameplay::update()
	{
		player->update();
	}
	void Gameplay::erase()
	{
		player->erase();
	}
	void Gameplay::draw()
	{
		player->draw();
	}
}
