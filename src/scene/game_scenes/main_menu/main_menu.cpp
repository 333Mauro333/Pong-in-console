#include "main_menu.h"

#include <iostream>

#include "game_values/game_values.h"
#include "managers/file_manager/file_manager.h"
#include "managers/game_manager/game_manager.h"
#include "managers/lives_manager/lives_manager.h"
#include "managers/music_manager/music_manager.h"
#include "managers/scene_manager/scene_manager.h"

using std::cout;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	MainMenu::MainMenu(int selectedOption) : Scene(COLOR::C_BLUE)
	{
		if (selectedOption < 1 || selectedOption > amountOfOptions)
		{
			selectedOption = 1;
		}

		gameTitle = FileManager::loadTitle();
		titleColor = COLOR::C_BWHITE;
		delayToDetect = 10;
		counter = 0;
		changeInThisFrame = true;

		normalColor = COLOR::C_GRAY;
		highlightedColor = COLOR::C_BWHITE;

		this->selectedOption = selectedOption;

		initOptions(selectedOption);
	}
	MainMenu::~MainMenu()
	{

	}

	void MainMenu::inputUpdate(int key)
	{
		if (keyIsPressed(MENU_CONTROLS::UP, key))
		{
			setPreviousOption();
		}
		else if (keyIsPressed(MENU_CONTROLS::DOWN, key))
		{
			setNextOption();
		}
		else if (keyIsPressed(MENU_CONTROLS::ENTER, key))
		{
			enterOption();
		}
	}
	void MainMenu::update()
	{
		if (canDetectInput())
		{
			resetCounter();
			saveOptionChangeInThisFrame(true);

			changeTitleColor();
		}
		else
		{
			discountCounter();
			saveOptionChangeInThisFrame(false);
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

		drawOptions();
	}


	void MainMenu::drawTitle()
	{
		int x = 0;
		int y = 1;

		char titleChar = (char)219; // █

		COLOR previousColor = ConsoleExt::getForegroundColor();


		x = getTitleWidth() / 2;

		ConsoleExt::goToCoordinates(x, y);
		ConsoleExt::setForegroundColor(titleColor);

		for (int i = 0; i < gameTitle.size(); i++)
		{
			if (gameTitle[i] == '*')
			{
				cout << titleChar;
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
	int MainMenu::getTitleWidth()
	{
		for (int i = 0; i < gameTitle.size(); i++)
		{
			if (gameTitle[i] == '_')
			{
				return i + 1;
			}
		}

		return 0;
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
		optionList[selectedOption - 1]->setColor(normalColor);

		if (selectedOption < amountOfOptions)
		{
			selectedOption++;
		}
		else
		{
			selectedOption = 1;
		}

		optionList[selectedOption - 1]->setColor(highlightedColor);
	}
	void MainMenu::setPreviousOption()
	{
		optionList[selectedOption - 1]->setColor(normalColor);

		if (selectedOption > 1)
		{
			selectedOption--;
		}
		else
		{
			selectedOption = amountOfOptions;
		}

		optionList[selectedOption - 1]->setColor(highlightedColor);
	}
	void MainMenu::enterOption()
	{
		switch (selectedOption)
		{
		case 1:
			LivesManager::setLives(GameValues::getInitialLives());
			SceneManager::loadScene(SCENE_TO_LOAD::GAMEPLAY);
			break;

		case 2:
			GameManager::quit();
			break;
		}
	}

	void MainMenu::initOptions(int selectedOption)
	{
		optionList[0] = new Text(ConsoleExt::getScreenWidth() / 2 - (5 + 2), 17, "JUGAR", COLOR::C_GRAY, true);
		optionList[1] = new Text(ConsoleExt::getScreenWidth() / 2 - (5 + 2), 20, "SALIR", COLOR::C_GRAY, true);

		optionList[selectedOption - 1]->setColor(highlightedColor);
	}
	
	bool MainMenu::keyIsPressed(MENU_CONTROLS keyToVerify, int pressedKey)
	{
		return ControlsManager::isPressed(pressedKey, keyToVerify);
	}
	bool MainMenu::canDetectInput()
	{
		return counter == 0;
	}
	void MainMenu::resetCounter()
	{
		counter = delayToDetect;
	}
	void MainMenu::saveOptionChangeInThisFrame(bool changed)
	{
		changeInThisFrame = changed;
	}
	void MainMenu::discountCounter()
	{
		counter--;
	}

	void MainMenu::drawOptions()
	{
		for (int i = 0; i < amountOfOptions; i++)
		{
			optionList[i]->draw();
		}
	}
}
