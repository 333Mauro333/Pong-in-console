#include "controls_manager.h"

#include "mgtv_library.h"

using namespace mgtv_library::console;


namespace pong_in_console
{
	int ControlsManager::menuUp = KEY_UP;
	int ControlsManager::menuDown = KEY_DOWN;
	int ControlsManager::menuLeft = KEY_LEFT;
	int ControlsManager::menuRight = KEY_RIGHT;
	int ControlsManager::menuEnter = KEY_ENTER;
	int ControlsManager::menuBack1 = KEY_ESC;
	int ControlsManager::menuBack2 = KEY_BACKSPACE;

	int ControlsManager::gameplayLeft = KEY_LEFT;
	int ControlsManager::gameplayRight = KEY_RIGHT;
	int ControlsManager::gameplayShoot = KEY_UP;

	bool ControlsManager::isPressed(int key, MENU_CONTROLS button)
	{
		switch (button)
		{
		case MENU_CONTROLS::UP:
			return menuUp == key;

		case MENU_CONTROLS::DOWN:
			return menuDown == key;

		case MENU_CONTROLS::LEFT:
			return menuLeft == key;

		case MENU_CONTROLS::RIGHT:
			return menuRight == key;

		case MENU_CONTROLS::ENTER:
			return menuEnter == key;

		case MENU_CONTROLS::BACK:
			return menuBack1 == key || menuBack2 == key;
		}

		return false;
	}
	bool ControlsManager::isPressed(int key, GAMEPLAY_CONTROLS button)
	{
		switch (button)
		{
		case GAMEPLAY_CONTROLS::LEFT:
			return gameplayLeft == key;

		case GAMEPLAY_CONTROLS::RIGHT:
			return gameplayRight == key;

		case GAMEPLAY_CONTROLS::SHOOT:
			return gameplayShoot == key;
		}

		return false;
	}
}
