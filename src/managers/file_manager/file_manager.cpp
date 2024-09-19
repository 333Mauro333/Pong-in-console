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
		ifstream titleReader;

		int length = 0;
		string text = "";
		char* content = NULL;


		titleReader.open("data/game_title.dat", ios::in | ios::binary);

		titleReader.read((char*)&length, sizeof(length));
		content = new char[length + 1];
		titleReader.read(content, length);
		content[length] = '\0';

		text = string(content);
		delete[] content;

		titleReader.close();

		return text;
	}

	string FileManager::loadLevel(int levelNumber)
	{
		ifstream titleReader;

		string filePath = "";
		int length = 0;
		string text = "";
		char* content = NULL;


		filePath = "data/level_" + to_string(levelNumber) + ".dat";

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
