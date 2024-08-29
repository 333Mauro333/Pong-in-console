#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene/scene.h"
#include "enums/scene_to_load.h"


namespace pong_in_console
{
	class SceneManager
	{
	public:
		static void loadScene(SCENE_TO_LOAD scene);
		static Scene* getActualScene();

	private:
		static Scene* actualScene;
	};
}

#endif // !SCENE_MANAGER_H
