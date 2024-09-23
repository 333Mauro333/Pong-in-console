#include "scene.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	Scene::Scene(COLOR backgroundColor)
	{
		ConsoleExt::setBackgroundColor(backgroundColor);

		system("cls");
	}
	Scene::~Scene()
	{

	}
}
