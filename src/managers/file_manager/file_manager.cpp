#include "file_manager.h"

#include <fstream>

using namespace std;


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
}
