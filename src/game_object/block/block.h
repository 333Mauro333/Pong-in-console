#ifndef BLOCK_H
#define BLOCK_H

#include "mgtv_library.h"

#include "enums/block_type.h"
#include "game_object/game_object.h"
#include "structs/picture.h"

using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Block : public GameObject
	{
	public:
		Block(int x, int y, BLOCK_TYPE blockType);
		virtual ~Block();

		void draw() override;

		BLOCK_TYPE getBlockType();

	protected:
		PICTURE picture;
		BLOCK_TYPE blockType;
	};
}

#endif // BLOCK_H
