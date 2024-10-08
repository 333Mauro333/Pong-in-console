#ifndef LIVES_MANAGER_H
#define LIVES_MANAGER_H

namespace pong_in_console
{
	class LivesManager
	{
	public:
		static void addALife();
		static void discountALife();

		static int getLives();
		static void setLives(int lives);

		static bool thereAreLives();

	private:
		static int lives;
	};
}

#endif // !LIVES_MANAGER_H
