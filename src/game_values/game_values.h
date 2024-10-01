#ifndef GAME_VALUES_H
#define GAME_VALUES_H

#include "enums/block_type.h"
#include "structs/picture.h"


namespace pong_in_console
{
	class GameValues
	{
	public:
		static void initValues();

		static PICTURE getBlockPicture(BLOCK_TYPE blockType);
		static int getBlockValue(BLOCK_TYPE blockType);
		static int getInitialLives();
		static void setInitialLives(int lives);

	private:
		static const int picturesQuantity = 5;
		static PICTURE blockPictures[picturesQuantity];

		static const int valueQuantity = 4;
		static int values[valueQuantity];

		static int initialLives;
		static int maxScore;

		static void initABlockPicture(int arrayPosition, char picture, COLOR color);
		static bool isDestructible(BLOCK_TYPE blockType);
	};
}

#endif // !GAME_VALUES_H
