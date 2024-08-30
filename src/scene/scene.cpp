#include "scene.h"

using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	COLOR Scene::backgroundColor = COLOR::C_BLACK;

	COLOR Scene::getBackgroundColor()
	{
		return backgroundColor;
	}
	void Scene::setBackgroundColor(COLOR newColor)
	{
		backgroundColor = newColor;
	}


	Scene::Scene()
	{
		ConsoleExt::setBackgroundColor(backgroundColor);

		system("cls");
	}
	Scene::~Scene()
	{

	}
}
