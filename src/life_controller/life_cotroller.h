#ifndef LIFE_CONTROLLER_H
#define LIFE_CONTROLLER_H

namespace pong_in_console
{
	class LifeController
	{
	public:
		LifeController();
		~LifeController();

		void addALife();
		void discountALife();

		int& getLives();
		void setLives(int lives);

		bool thereAreLives();

	private:
		int lives;
	};
}

#endif // !LIFE_CONTROLLER_H
