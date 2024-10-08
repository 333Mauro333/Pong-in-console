#include "level_passed.h"

#include <string>

#include "mgtv_library.h"

#include "managers/controls_manager/controls_manager.h"
#include "managers/level_manager/level_manager.h"
#include "managers/level_time_manager/level_time_manager.h"
#include "managers/scene_manager/scene_manager.h"
#include "managers/score_manager/score_manager.h"

using std::string;
using std::to_string;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	LevelPassed::LevelPassed() : Scene()
	{
		itWasDrawn = false;
		time = LevelTimeManager::getActualTime();
		pointsForBlockDestruction = ScoreManager::getBlocksScore();
		initPointsForTime();
		pointsEarned = pointsForBlockDestruction + pointsForTime;
		totalPoints = ScoreManager::getTotalScore() + pointsEarned;
	}
	LevelPassed::~LevelPassed()
	{

	}

	void LevelPassed::inputUpdate(int key)
	{
		if (ControlsManager::isPressed(key, MENU_CONTROLS::ENTER))
		{
			ScoreManager::saveTotalScore(totalPoints);
			ScoreManager::resetBlocksScore();

			if (LevelManager::getLevel() < 3)
			{
				LevelManager::addLevel();
				SceneManager::loadScene(SCENE_TO_LOAD::GAMEPLAY);
			}
			else
			{
				SceneManager::loadScene(SCENE_TO_LOAD::MAIN_MENU);
			}
		}
	}
	void LevelPassed::update()
	{

	}
	void LevelPassed::erase()
	{

	}
	void LevelPassed::draw()
	{
		if (!itWasDrawn)
		{
			drawFrames();

			writePointsForBlockDestruction(8);
			writePointsForTime(11);
			writePointsEarned(14);
			writeTotalPoints(20);
		}
	}


	void LevelPassed::drawFrames()
	{
		int windowWidth = ConsoleExt::getScreenWidth();
		int windowHeight = ConsoleExt::getScreenHeight();
		COLOR framesColor = COLOR::C_YELLOW;


		ConsoleExt::drawFrame(0, 0, windowWidth - 1, windowHeight - 1, framesColor);
		ConsoleExt::drawFrame(2, 1, windowWidth - 3, windowHeight - 2, framesColor);
	}

	void LevelPassed::writePointsForBlockDestruction(int y)
	{
		char oWithAccent = (char)162; // ó
		string pointsMessage = "";

		pointsMessage += "PUNTOS POR DESTRUCCI";
		pointsMessage += oWithAccent;
		pointsMessage += "N DE BLOQUES:";

		ConsoleExt::goToCoordinates(textsColumn, y);
		ConsoleExt::writeWithColor(pointsMessage, COLOR::C_LRED);
		ConsoleExt::goToCoordinates(numbersColumn, y);
		ConsoleExt::writeWithColor(to_string(pointsForBlockDestruction), COLOR::C_LRED);
	}
	void LevelPassed::writePointsForTime(int y)
	{
		ConsoleExt::goToCoordinates(textsColumn, y);
		ConsoleExt::writeWithColor("PUNTOS POR TIEMPO:", COLOR::C_LRED);
		ConsoleExt::goToCoordinates(numbersColumn, y);
		ConsoleExt::writeWithColor(to_string(pointsForTime), COLOR::C_LRED);
	}
	void LevelPassed::writePointsEarned(int y)
	{
		ConsoleExt::goToCoordinates(textsColumn, y);
		ConsoleExt::writeWithColor("PUNTOS GANADOS: ", COLOR::C_LRED);
		ConsoleExt::goToCoordinates(numbersColumn, y);
		ConsoleExt::writeWithColor(to_string(pointsEarned), COLOR::C_LRED);
	}
	void LevelPassed::writeTotalPoints(int y)
	{
		ConsoleExt::goToCoordinates(textsColumn, y);
		ConsoleExt::writeWithColor("PUNTAJE TOTAL: ", COLOR::C_LRED);
		ConsoleExt::goToCoordinates(numbersColumn, y);
		ConsoleExt::writeWithColor(to_string(totalPoints), COLOR::C_LRED);
	}

	void LevelPassed::initPointsForTime()
	{
		if (time < 60)
		{
			pointsForTime = 10000;
		}
		else if (time < 90)
		{
			pointsForTime = 7500;
		}
		else if (time < 120)
		{
			pointsForTime = 5000;
		}
		else if (time < 180)
		{
			pointsForTime = 2500;
		}
		else if (time < 300)
		{
			pointsForTime = 1000;
		}
		else
		{
			pointsForTime = 0;
		}
	}
}
