#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>

#include "scene/scene.h"

using namespace std;


namespace pong_in_console
{
	class MainMenu : public Scene
	{
	public:
		MainMenu(int selectedOption = 1);
		~MainMenu();

		void inputUpdate(int key) override;
		void update() override;
		void erase() override;
		void draw() override;

	private:
		static const int amountOfOptions = 5;
		string optionList[amountOfOptions];

		int option;

		void highlightOption();
	};
}

#endif // !MAIN_MENU_H
