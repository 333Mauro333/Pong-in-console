#include "file_manager.h"

#include <fstream>
#include <iostream>

using std::ifstream;
using std::ios;
using std::to_string;


namespace pong_in_console
{
	string FileManager::loadTitle()
	{
		return getInformationInText(INFORMATION_TO_LOAD::TITLE);
	}
	string FileManager::loadLevel(int levelNumber)
	{
		INFORMATION_TO_LOAD level = (INFORMATION_TO_LOAD)levelNumber;

		return getInformationInText(level);
	}


	string FileManager::getInformationInText(INFORMATION_TO_LOAD informationToLoad)
	{
		ifstream titleReader;
		string filePath = "";
		int length = 0;
		char* content = NULL;
		string text = "";


		switch (informationToLoad)
		{
		case INFORMATION_TO_LOAD::TITLE:
			filePath = "data/game_title.dat";
			break;

		case INFORMATION_TO_LOAD::LEVEL_1:
			int levelNumber = (int)informationToLoad;

			filePath = "data/level_" + to_string(levelNumber) + ".dat";
			break;
		}

		titleReader.open(filePath.c_str(), ios::in | ios::binary);

		titleReader.read((char*)&length, sizeof(length));
		content = new char[length + 1];
		titleReader.read(content, length);

		content[length] = '\0';
		text = string(content);

		delete[] content;
		titleReader.close();

		return text;
	}
}
