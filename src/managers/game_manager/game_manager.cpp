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
	bool GameManager::inGame = true;

	void GameManager::quit()
	{
		inGame = false;
	}

	GameManager::GameManager(string title, SCENE_TO_LOAD scene)
	{
		this->title = title;
		sceneToLoad = scene;
	}
	GameManager::~GameManager()
	{
		delete SceneManager::getActualScene();

		LaserPooling::destroyLasers();
		ConsoleExt::goToCoordinates(0, 24);
		MusicManager::closeMusicSystem();
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
	}

	void GameManager::init(string title)
	{
		ConsoleExt::hideCursor();
		ConsoleExt::setConsoleTitle(title);
		MusicManager::initMusicSystem();
		GameValues::initValues();
		SceneManager::loadScene(sceneToLoad);
		LaserPooling::initLasers();
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
}
