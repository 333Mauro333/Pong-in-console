#include "game_manager.h"

#include <thread>

#include "mgtv_library.h"

#include "game_values/game_values.h"
#include "managers/music_manager/music_manager.h"

using std::thread;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	bool GameManager::inGame = true;
	SCENE_TO_LOAD GameManager::sceneToLoad = SCENE_TO_LOAD::MAIN_MENU;
	SCENE_TO_LOAD GameManager::sceneToChange = sceneToLoad;


	void GameManager::run(string title)
	{
		init(title);

		while (inGame)
		{
			ConsoleExt::sleep(3);

			inputUpdate();
			update();
			draw();
		}

		destroy();
	}
	void GameManager::quit()
	{
		inGame = false;
	}


	void GameManager::init(string title)
	{
		ConsoleExt::hideCursor();
		ConsoleExt::setConsoleTitle(title);
		MusicManager::initMusic();
		GameValues::initValues();
		SceneManager::loadScene(sceneToLoad, COLOR::C_BLUE);
	}
	void GameManager::inputUpdate()
	{
		int key = ConsoleExt::getKey(false);

		SceneManager::getActualScene()->inputUpdate(key);
	}
	void GameManager::update()
	{
		thread musicThread(MusicManager::updateMusicStream);
		musicThread.join();

		SceneManager::getActualScene()->update();
	}
	void GameManager::draw()
	{
		SceneManager::getActualScene()->erase();
		SceneManager::getActualScene()->draw();
	}
	void GameManager::destroy()
	{
		delete SceneManager::getActualScene();

		MusicManager::closeMusicSistem();
	}
}
