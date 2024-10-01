﻿#include "game_values.h"


namespace pong_in_console
{
	PICTURE GameValues::blockPictures[GameValues::picturesQuantity] = {};
	int GameValues::values[GameValues::valueQuantity] = { 5, 10, 25, 50 };
	int GameValues::initialLives = 5;
	int GameValues::maxScore = 0;


	void GameValues::initValues()
	{
		initABlockPicture(0, (char)254, COLOR::C_GRAY); // 254: ■
		initABlockPicture(1, (char)247, COLOR::C_RED); // 247: ≈
		initABlockPicture(2, '=', COLOR::C_YELLOW);
		initABlockPicture(3, (char)240, COLOR::C_GREEN); // 240: ≡
		initABlockPicture(4, '#', COLOR::C_BLUE);
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
