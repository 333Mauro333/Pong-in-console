#ifndef SCENE_H
#define SCENE_H

#include "mgtv_library.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Scene
	{
	public:
		static COLOR getBackgroundColor();
		static void setBackgroundColor(COLOR newColor);


		Scene();
		virtual ~Scene();

		virtual void inputUpdate(int key) = 0;
		virtual void update() = 0;
		virtual void erase() = 0;
		virtual void draw() = 0;

	protected:
		static COLOR backgroundColor;
	};
}

#endif // !SCENE_H
