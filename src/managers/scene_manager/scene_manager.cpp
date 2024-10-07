#include "scene_manager.h"

#include "scene/game_scenes/gameplay/gameplay.h"
#include "scene/game_scenes/level_passed/level_passed.h"
#include "scene/game_scenes/main_menu/main_menu.h"
#include "scene/game_scenes/null_scene/null_scene.h"


namespace pong_in_console
{
	Scene* SceneManager::actualScene = new NullScene();

	void SceneManager::loadScene(SCENE_TO_LOAD scene)
	{
		delete actualScene;

		switch (scene)
		{
		case SCENE_TO_LOAD::MAIN_MENU:
			actualScene = new MainMenu();
			break;

		case SCENE_TO_LOAD::GAMEPLAY:
			actualScene = new Gameplay();
			break;

		case SCENE_TO_LOAD::LEVEL_PASSED:
			actualScene = new LevelPassed();
			break;
		}
	}
	Scene* SceneManager::getActualScene()
	{
		return actualScene;
	}
}
