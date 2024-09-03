#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "mgtv_library.h"

#include "scene/scene.h"
#include "enums/scene_to_load.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class SceneManager
	{
	public:
		static void loadScene(SCENE_TO_LOAD scene);
		static void loadScene(SCENE_TO_LOAD scene, COLOR backgroundColor);
		static Scene* getActualScene();

	private:
		static Scene* actualScene;
	};
}

#endif // !SCENE_MANAGER_H
