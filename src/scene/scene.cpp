#include "scene.h"


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
