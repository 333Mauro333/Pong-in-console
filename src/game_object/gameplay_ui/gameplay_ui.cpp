#include "gameplay_ui.h"

#include <iostream>

#include "mgtv_library.h"

using std::to_string;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	GameplayUI::GameplayUI(Frame* frame, int height) : GameObject(frame->getLeft(), frame->getPosition().y - height + 1, 42, height)
	{
		lives = NULL;
		level = NULL;
		score = NULL;
		time = NULL;

		itWasDrown = false;
		updateLives = false;
		updateLevel = false;
		updateScore = false;
		updateTime = false;
	}
	GameplayUI::~GameplayUI()
	{

	}


	void GameplayUI::pointToLives(int& lives)
	{
		this->lives = &lives;
	}
	void GameplayUI::pointToLevel(int& level)
	{
		this->level = &level;
	}
	void GameplayUI::pointToScore(int& score)
	{
		this->score = &score;
	}
	void GameplayUI::pointToTime(long long& time)
	{
		this->time = &time;
	}

	void GameplayUI::updateStatistic(GAMEPLAY_STATISTIC statisticToUpdate)
	{
		switch (statisticToUpdate)
		{
		case GAMEPLAY_STATISTIC::LIVES:
			updateLives = true;
			break;

		case GAMEPLAY_STATISTIC::LEVEL:
			updateLevel = true;
			break;

		case GAMEPLAY_STATISTIC::SCORE:
			updateScore = true;
			break;

		case GAMEPLAY_STATISTIC::TIME:
			updateTime = true;
			break;
		}
	}

	void GameplayUI::draw()
	{
		if (!itWasDrown)
		{
			itWasDrown = true;

			drawFrame();
			drawLeftBorderConection();
			drawRightBorderConection();
			drawColumn(8);
			drawColumn(16);
			drawColumn(27);

			writeLives();
			writeLevel();
			writeTime();
			writeScore();
		}

		if (updateLives)
		{
			updateLives = false;
			writeLives();
		}

		if (updateLevel)
		{
			updateLevel = false;
			writeLevel();
		}

		if (updateTime)
		{
			updateTime = false;
			writeTime();
		}

		if (updateScore)
		{
			updateScore = false;
			writeScore();
		}
	}


	void GameplayUI::drawFrame()
	{
		ConsoleExt::drawFrame(position.x, position.y,
							  position.x + size.w - 1, position.y + size.h - 1);
	}
	void GameplayUI::drawLeftBorderConection()
	{
		string character = "";

		character += (char)204; // ╠
		ConsoleExt::goToCoordinates(position.x, position.y + size.h - 1);
		ConsoleExt::writeWithColor(character, ConsoleExt::getForegroundColor());
	}
	void GameplayUI::drawRightBorderConection()
	{
		string character = "";

		character += (char)185; // ╣
		ConsoleExt::goToCoordinates(position.x + size.w - 1, position.y + size.h - 1);
		ConsoleExt::writeWithColor(character, ConsoleExt::getForegroundColor());
	}
	void GameplayUI::drawColumn(int positionXOverTheFrame)
	{
		string character = "";

		character += (char)203; // ╦
		ConsoleExt::goToCoordinates(position.x + positionXOverTheFrame, position.y);
		ConsoleExt::writeWithColor(character, ConsoleExt::getForegroundColor());
		character = "";
		character += (char)186; // ║

		for (int i = 0; i < 3; i++)
		{
			ConsoleExt::goToCoordinates(position.x + positionXOverTheFrame, position.y + i + 1);
			ConsoleExt::writeWithColor(character, ConsoleExt::getForegroundColor());
		}

		character = "";
		character += (char)202; // ╩
		ConsoleExt::goToCoordinates(position.x + positionXOverTheFrame, position.y + 4);
		ConsoleExt::writeWithColor(character, ConsoleExt::getForegroundColor());
	}

	void GameplayUI::writeLives()
	{
		COLOR color = ConsoleExt::getForegroundColor();

		if (*lives == 0)
		{
			color = COLOR::C_RED;
		}

		ConsoleExt::goToCoordinates(position.x + 1, position.y + 2);
		ConsoleExt::writeWithColor("VIDAS:", color);
		ConsoleExt::writeWithColor(to_string(*lives), color);
	}
	void GameplayUI::writeLevel()
	{
		ConsoleExt::goToCoordinates(position.x + 9, position.y + 2);
		ConsoleExt::writeWithColor("NIVEL:", ConsoleExt::getForegroundColor());
		ConsoleExt::writeWithColor(to_string(*level), ConsoleExt::getForegroundColor());
	}
	void GameplayUI::writeTime()
	{
		ConsoleExt::goToCoordinates(position.x + 17, position.y + 2);
		ConsoleExt::writeWithColor("TIEMPO:", ConsoleExt::getForegroundColor());
		writeCountWithZeros(3);
	}
	void GameplayUI::writeCountWithZeros(int amountOfZeros)
	{
		string timeWithZeros = to_string(*time);

		while (timeWithZeros.size() < amountOfZeros)
		{
			timeWithZeros = "0" + timeWithZeros;
		}

		ConsoleExt::goToCoordinates(position.x + 24, position.y + 2);
		ConsoleExt::writeWithColor(timeWithZeros, ConsoleExt::getForegroundColor());
	}
	void GameplayUI::writeScore()
	{
		ConsoleExt::goToCoordinates(position.x + 28, position.y + 2);
		ConsoleExt::writeWithColor("PUNTAJE:", ConsoleExt::getForegroundColor());
		writeScoreWithZeros(5);
	}
	void GameplayUI::writeScoreWithZeros(int amountOfZeros)
	{
		string timeWithZeros = to_string(*score);

		while (timeWithZeros.size() < amountOfZeros)
		{
			timeWithZeros = "0" + timeWithZeros;
		}

		ConsoleExt::goToCoordinates(position.x + 36, position.y + 2);
		ConsoleExt::writeWithColor(timeWithZeros, ConsoleExt::getForegroundColor());
	}
}
