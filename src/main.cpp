#include <iostream>
#include <fstream>

#include "managers/game_manager/game_manager.h"
#include "managers/file_manager/file_manager.h"

using namespace std;
using namespace pong_in_console;


int main()
{
	//GameManager::run("PONG");

	string title = FileManager::loadTitle();

	for (int i = 0; i < title.size(); i++)
	{
		if (title[i] == '*')
		{
			cout << (char)219;
		}
		else if (title[i] == '-')
		{
			cout << " ";
		}
		else if (title[i] == '_')
		{
			cout << endl;
		}
		else
		{
			cout << title[i];
		}
	}




	return 0;
}
