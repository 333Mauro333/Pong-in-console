#include "managers/game_manager/game_manager.h"

using pong_in_console::GameManager;
using pong_in_console::SCENE_TO_LOAD;


int main()
{
	GameManager* gameManager = new GameManager("PONG in console", SCENE_TO_LOAD::MAIN_MENU);


	gameManager->run();

	delete gameManager;

	return 0;
}
