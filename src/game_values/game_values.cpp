﻿#include "game_values.h"


namespace pong_in_console
{
	PICTURE GameValues::blockPictures[GameValues::picturesQuantity] = {};
	int GameValues::values[GameValues::valueQuantity] = { 10, 25, 50, 100 };


	void GameValues::initValues()
	{
		initABlockPicture(0, (char)247, COLOR::C_RED); // 247: ≈
		initABlockPicture(1, '=', COLOR::C_YELLOW);
		initABlockPicture(2, (char)240, COLOR::C_GREEN); // 240: ≡
		initABlockPicture(3, '#', COLOR::C_BLUE);
		initABlockPicture(4, (char)254, COLOR::C_GRAY); // 254: ■
	}

	PICTURE GameValues::getBlockPicture(BLOCK_TYPE blockType)
	{
		return blockPictures[(int)blockType];
	}
	int GameValues::getBlockValue(BLOCK_TYPE blockType)
	{
		if (blockType != BLOCK_TYPE::B_INDESTRUCTIBLE)
		{
			return values[(int)blockType];
		}

		return 0;
	}


	void GameValues::initABlockPicture(int arrayPosition, char picture, COLOR color)
	{
		blockPictures[arrayPosition].picture = picture;
		blockPictures[arrayPosition].color = color;
	}
}
