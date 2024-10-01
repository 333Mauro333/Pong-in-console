#include "life_cotroller.h"


namespace pong_in_console
{
	LifeController::LifeController()
	{
		lives = 3;
	}
	LifeController::~LifeController()
	{

	}


	void LifeController::addALife()
	{
		lives++;
	}
	void LifeController::discountALife()
	{
		lives--;
	}

	int& LifeController::getLives()
	{
		return lives;
	}
	void LifeController::setLives(int lives)
	{
		this->lives = lives;
	}

	bool LifeController::thereAreNoLives()
	{
		return lives <= 0;
	}
}
