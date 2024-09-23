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
		static void run(string title);
		static void quit();

	private:
		static bool inGame;
		static SCENE_TO_LOAD sceneToLoad;

		static void init(string title);
		static void inputUpdate();
		static void update();
		static void draw();
		static void destroy();
	};
}

#endif // !GAME_MANAGER_H
