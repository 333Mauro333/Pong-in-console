#include "game_manager.h"

#include <iostream>
#include <thread>

#include "mgtv_library.h"

#include "managers/scene_manager/scene_manager.h"
#include "managers/music_manager/music_manager.h"

using namespace mgtv_library::console;


namespace pong_in_console
{
	bool GameManager::inGame = true;
	SCENE_TO_LOAD GameManager::sceneToLoad = SCENE_TO_LOAD::GAMEPLAY;
	SCENE_TO_LOAD GameManager::sceneToChange = sceneToLoad;


	void GameManager::run(string title)
	{
		ConsoleExt::hideCursor();
		ConsoleExt::setConsoleTitle(title);
		MusicManager::initMusic();
		Scene::setBackgroundColor(COLOR::C_BLUE);
		SceneManager::loadScene(sceneToLoad);

		system("cls");

		while (inGame)
		{
			ConsoleExt::sleep(3);

			inputUpdate();
			update();
			draw();

			checkValueChanges();
		}

		delete SceneManager::getActualScene();

		MusicManager::closeMusic();
	}
	void GameManager::quit()
	{
		inGame = false;
	}


	void GameManager::inputUpdate()
	{
		int key = ConsoleExt::getKey(false);

		SceneManager::getActualScene()->inputUpdate(key);
	}
	void GameManager::update()
	{
		std::thread miHilo(MusicManager::updateMusicStream);
		miHilo.join();

		SceneManager::getActualScene()->update();
	}
	void GameManager::draw()
	{
		SceneManager::getActualScene()->erase();
		SceneManager::getActualScene()->draw();
	}

	void GameManager::checkValueChanges()
	{
		if (sceneToLoad != sceneToChange)
		{
			SceneManager::loadScene(sceneToChange);

			sceneToLoad = sceneToChange;
		}
	}
}
