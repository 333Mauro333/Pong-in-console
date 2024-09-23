#ifndef CONTROLS_MANAGER_H
#define CONTROLS_MANAGER_H

#include "enums/gameplay_controls.h"
#include "enums/menu_controls.h"


namespace pong_in_console
{
	class ControlsManager
	{
	public:
		static bool isPressed(int key, MENU_CONTROLS button);
		static bool isPressed(int key, GAMEPLAY_CONTROLS button);

	private:
		static int menuUp;
		static int menuDown;
		static int menuLeft;
		static int menuRight;
		static int menuEnter;
		static int menuBack1;
		static int menuBack2;

		static int gameplayLeft;
		static int gameplayRight;
		static int gameplayShoot;
	};
}

#endif // !CONTROLS_MANAGER_H
