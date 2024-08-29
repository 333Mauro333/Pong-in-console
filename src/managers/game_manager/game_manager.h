#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>

#include "enums/scene_to_load.h"

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
		static SCENE_TO_LOAD sceneToChange;

		static void inputUpdate();
		static void update();
		static void draw();

		static void checkValueChanges();
	};
}

#endif // !GAME_MANAGER_H
