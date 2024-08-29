#include "scene.h"


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

	}
	Scene::~Scene()
	{

	}
}
