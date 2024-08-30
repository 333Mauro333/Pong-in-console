#include "main_menu.h"

#include <iostream>

#include "managers/controls_manager/controls_manager.h"
#include "managers/file_manager/file_manager.h"
#include "managers/game_manager/game_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"

using std::cout;


namespace pong_in_console
{
	MainMenu::MainMenu(int selectedOption)
	{
		int checkedOption = selectedOption;

		//MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		gameTitle = FileManager::loadTitle();
		titleColor = COLOR::C_BWHITE;
		delayTime = 10;
		timer = 0;
		changeInThisFrame = true;

		normalColor = COLOR::C_GRAY;
		highlightedColor = COLOR::C_BWHITE;

		optionList[0] = new Text(ConsoleExt::getScreenWidth() / 2 - (5 + 2), 17, "JUGAR", COLOR::C_GRAY, true);
		optionList[1] = new Text(ConsoleExt::getScreenWidth() / 2 - (5 + 2), 20, "SALIR", COLOR::C_GRAY, true);

		if (selectedOption < 1 || selectedOption > amountOfOptions)
		{
			checkedOption = 1;
		}

		optionList[checkedOption - 1]->setColor(highlightedColor);

		option = selectedOption;
	}
	MainMenu::~MainMenu()
	{

	}

	void MainMenu::inputUpdate(int key)
	{
		if (ControlsManager::isPressed(key, MENU_CONTROLS::UP))
		{
			setPreviousOption();
		}
		else if (ControlsManager::isPressed(key, MENU_CONTROLS::DOWN))
		{
			setNextOption();
		}
		else if (ControlsManager::isPressed(key, MENU_CONTROLS::ENTER))
		{
			enterOption();
		}
	}
	void MainMenu::update()
	{
		if (timer <= 0)
		{
			timer = delayTime;
			changeInThisFrame = true;

			changeTitleColor();
		}
		else
		{
			timer--;
			changeInThisFrame = false;
		}
	}
	void MainMenu::erase()
	{

	}
	void MainMenu::draw()
	{
		if (changeInThisFrame)
		{
			drawTitle();
		}

		for (int i = 0; i < amountOfOptions; i++)
		{
			optionList[i]->draw();
		}
	}


	void MainMenu::drawTitle()
	{
		int x = 0;
		int y = 1;

		int titleWidth = 0;

		COLOR previousColor = ConsoleExt::getForegroundColor();


		for (int i = 0; i < gameTitle.size() && titleWidth == 0; i++)
		{
			if (gameTitle[i] == '_')
			{
				titleWidth = i + 1;
				x = ConsoleExt::getScreenWidth() / 2 - titleWidth / 2;
			}
		}

		ConsoleExt::goToCoordinates(x, y);

		ConsoleExt::setForegroundColor(titleColor);

		for (int i = 0; i < gameTitle.size(); i++)
		{
			if (gameTitle[i] == '*')
			{
				cout << (char)219;
			}
			else if (gameTitle[i] == '-')
			{
				cout << " ";
			}
			else if (gameTitle[i] == '_')
			{
				y++;

				ConsoleExt::goToCoordinates(x, y);
			}
			else
			{
				cout << gameTitle[i];
			}
		}

		ConsoleExt::setForegroundColor(previousColor);
	}
	void MainMenu::changeTitleColor()
	{
		if (titleColor == COLOR::C_BWHITE)
		{
			titleColor = COLOR::C_LBLUE;
		}
		else
		{
			titleColor = COLOR::C_BWHITE;
		}
	}

	void MainMenu::setNextOption()
	{
		optionList[option - 1]->setColor(normalColor);

		if (option < amountOfOptions)
		{
			option++;
		}
		else
		{
			option = 1;
		}

		optionList[option - 1]->setColor(highlightedColor);
	}
	void MainMenu::setPreviousOption()
	{
		optionList[option - 1]->setColor(normalColor);

		if (option > 1)
		{
			option--;
		}
		else
		{
			option = amountOfOptions;
		}

		optionList[option - 1]->setColor(highlightedColor);
	}
	void MainMenu::enterOption()
	{
		switch (option)
		{
		case 1:
			Scene::setBackgroundColor(COLOR::C_BLACK);
			SceneManager::loadScene(SCENE_TO_LOAD::GAMEPLAY);
			break;

		case 2:
			GameManager::quit();
			break;
		}
	}
}
