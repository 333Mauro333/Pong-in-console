#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>

#include "enums/scene_to_load.h"
#include "managers/scene_manager/scene_manager.h"

using std::string;


namespace pong_in_console
{
	class GameManager
	{
	public:
		static void quit();

		GameManager(string title, SCENE_TO_LOAD scene = SCENE_TO_LOAD::MAIN_MENU);
		~GameManager();

		void run();

	private:
		static bool inGame;

		string title;
		SCENE_TO_LOAD sceneToLoad;

		void init(string title);
		void inputUpdate();
		void update();
		void draw();
	};
}

#endif // !GAME_MANAGER_H
