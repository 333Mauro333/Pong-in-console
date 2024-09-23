#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>

#include "game_object/text/text.h"
#include "managers/controls_manager/controls_manager.h"
#include "scene/scene.h"

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
		int delayToDetect;
		int counter;
		bool changeInThisFrame;

		static const int amountOfOptions = 2;
		Text* optionList[amountOfOptions];
		int selectedOption;

		COLOR normalColor;
		COLOR highlightedColor;

		void drawTitle();
		void changeTitleColor();

		void setNextOption();
		void setPreviousOption();
		void enterOption();

		void initOptions(int selectedOption);

		bool keyIsPressed(MENU_CONTROLS keyToVerify, int pressedKey);
		bool canDetectInput();
		void resetCounter();
		void saveOptionChangeInThisFrame(bool changed);
		void discountCounter();

		void drawOptions();
	};
}

#endif // !MAIN_MENU_H
