#ifndef SCENE_H
#define SCENE_H

#include "mgtv_library.h"

using mgtv_library::console::COLOR;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	class Scene
	{
	public:
		Scene(COLOR backgroundColor = ConsoleExt::getBackgroundColor());
		virtual ~Scene();

		virtual void inputUpdate(int key) = 0;
		virtual void update() = 0;
		virtual void erase() = 0;
		virtual void draw() = 0;
	};
}

#endif // !SCENE_H
