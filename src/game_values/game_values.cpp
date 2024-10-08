#include "game_values.h"


namespace pong_in_console
{
	PICTURE GameValues::blockPictures[GameValues::picturesQuantity] = {};
	int GameValues::values[GameValues::valueQuantity] = { 5, 10, 20, 30 };
	int GameValues::initialLives = 3;
	int GameValues::maxScore = 0;

	void GameValues::initValues()
	{
		char metalBlockPicture = (char)254; //  ■
		char redBlockPicture = (char)247; // ≈
		char yellowBlockPicture = '=';
		char greenBlockPicture = (char)240; // ≡
		char blueBlockPicture = '#';

		initABlockPicture(0, metalBlockPicture, COLOR::C_GRAY);
		initABlockPicture(1, redBlockPicture, COLOR::C_RED);
		initABlockPicture(2, yellowBlockPicture, COLOR::C_YELLOW);
		initABlockPicture(3, greenBlockPicture, COLOR::C_GREEN);
		initABlockPicture(4, blueBlockPicture, COLOR::C_BLUE);
	}

	PICTURE GameValues::getBlockPicture(BLOCK_TYPE blockType)
	{
		return blockPictures[(int)blockType];
	}
	int GameValues::getBlockValue(BLOCK_TYPE blockType)
	{
		if (isDestructible(blockType))
		{
			return values[(int)blockType];
		}

		return 0;
	}
	int GameValues::getInitialLives()
	{
		return initialLives;
	}
	void GameValues::setInitialLives(int lives)
	{
		initialLives = lives;
	}


	void GameValues::initABlockPicture(int arrayPosition, char picture, COLOR color)
	{
		blockPictures[arrayPosition].picture = picture;
		blockPictures[arrayPosition].color = color;
	}
	bool GameValues::isDestructible(BLOCK_TYPE blockType)
	{
		return blockType != BLOCK_TYPE::B_INDESTRUCTIBLE;
	}
}
