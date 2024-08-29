#include "main_menu.h"

#include "managers/music_manager/music_manager.h"


namespace pong_in_console
{
	MainMenu::MainMenu(int selectedOption)
	{
		MusicManager::play(MUSIC_TO_PLAY::MAIN_MENU);

		optionList[0] = "JUGAR";
		optionList[1] = "OPCIONES";
		optionList[2] = "AYUDA";
		optionList[3] = "PUNTAJES ALTOS";
		optionList[4] = "SALIR";

		option = selectedOption;
	}
	MainMenu::~MainMenu()
	{

	}

	void MainMenu::inputUpdate(int key)
	{

	}
	void MainMenu::update()
	{

	}
	void MainMenu::erase()
	{

	}
	void MainMenu::draw()
	{

	}


	void MainMenu::highlightOption()
	{

	}
}
