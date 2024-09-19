#include "scene_manager.h"

#include "scene/game_scenes/gameplay/gameplay.h"
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
			actualScene = new Gameplay(1);
			break;
		}

		system("cls");
	}
	void SceneManager::loadScene(SCENE_TO_LOAD scene, COLOR backgroundColor)
	{
		delete actualScene;

		switch (scene)
		{
		case SCENE_TO_LOAD::MAIN_MENU:
			actualScene = new MainMenu();
			break;

		case SCENE_TO_LOAD::GAMEPLAY:
			actualScene = new Gameplay(1);
			break;
		}

		Scene::setBackgroundColor(backgroundColor);

		system("cls");
	}
	void SceneManager::loadScene(int levelNumber, COLOR backgroundColor)
	{
		delete actualScene;

		actualScene = new Gameplay(levelNumber);

		Scene::setBackgroundColor(backgroundColor);

		system("cls");
	}

	Scene* SceneManager::getActualScene()
	{
		return actualScene;
	}
}
