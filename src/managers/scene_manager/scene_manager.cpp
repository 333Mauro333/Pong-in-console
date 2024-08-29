#include "scene_manager.h"

#include "scene/game_scenes/gameplay/gameplay.h"


namespace pong_in_console
{
	Scene* SceneManager::actualScene = NULL;

	void SceneManager::loadScene(SCENE_TO_LOAD scene)
	{
		if (actualScene != NULL)
		{
			delete actualScene;
		}

		switch (scene)
		{
		case SCENE_TO_LOAD::MAIN_MENU:
			//actualScene = new MainMenu();
			break;

		case SCENE_TO_LOAD::GAMEPLAY:
			actualScene = new Gameplay();
			break;
		}
	}
	Scene* SceneManager::getActualScene()
	{
		return actualScene;
	}
}
