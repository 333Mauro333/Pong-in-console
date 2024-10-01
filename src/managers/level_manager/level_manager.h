#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

namespace pong_in_console
{
	class LevelManager
	{
	public:
		static void addLevel();

		static int getLevel();
		static void setLevel(int newLevel);

	private:
		static int gameLevel;
	};
}

#endif // !LEVEL_MANAGER_H
