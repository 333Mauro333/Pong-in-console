#ifndef NULL_SCENE_H
#define NULL_SCENE_H

#include "scene/scene.h"


namespace pong_in_console
{
	class NullScene : public Scene
	{
	public:
		NullScene();
		~NullScene();

		void inputUpdate(int key) override;
		void update() override;
		void erase() override;
		void draw() override;
	};
}

#endif // !NULL_SCENE_H
