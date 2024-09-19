#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

using std::string;


namespace pong_in_console
{
	class FileManager
	{
	public:
		static string loadTitle();

		static string loadLevel(int levelNumber);
	};
}

#endif // !FILE_MANAGER_H
