#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>

#include "scene/scene.h"
#include "game_object/text/text.h"

using std::string;


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
		string gameTitle;
		COLOR titleColor;
		int delayTime;
		int timer;
		bool changeInThisFrame;

		static const int amountOfOptions = 2;
		Text* optionList[amountOfOptions];

		COLOR normalColor;
		COLOR highlightedColor;

		int option;

		void drawTitle();
		void changeTitleColor();

		void setNextOption();
		void setPreviousOption();
		void enterOption();
	};
}

#endif // !MAIN_MENU_H
