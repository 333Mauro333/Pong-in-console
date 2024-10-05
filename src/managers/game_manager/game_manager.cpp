#include "game_manager.h"

#include <thread>

#include "mgtv_library.h"

#include "game_values/game_values.h"
#include "laser_pooling/laser_pooling.h"
#include "managers/music_manager/music_manager.h"

using std::thread;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	GameManager* GameManager::instance = NULL;

	GameManager* GameManager::getInstance()
	{
		return instance;
	}

	GameManager::GameManager(string title, SCENE_TO_LOAD scene)
	{
		if (instance == NULL)
		{
			instance = this;
			this->title = title;
			inGame = true;
			sceneToLoad = scene;
		}
		else
		{
			delete this;
		}
	}
	GameManager::~GameManager()
	{

	}

	void GameManager::run()
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
		SceneManager::loadScene(sceneToLoad);

		LaserPooling* laserPooling = new LaserPooling(4);
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
		delete LaserPooling::getInstance();

		ConsoleExt::goToCoordinates(0, 24);
		MusicManager::closeMusicSistem();
	}
}
