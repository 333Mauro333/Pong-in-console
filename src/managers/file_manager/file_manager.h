#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

#include "enums/information_to_load.h"

using std::string;


namespace pong_in_console
{
	class FileManager
	{
	public:
		static string loadTitle();
		static string loadLevel(int levelNumber);

	private:
		static string getInformationInText(INFORMATION_TO_LOAD informationToLoad);
	};
}

#endif // !FILE_MANAGER_H
