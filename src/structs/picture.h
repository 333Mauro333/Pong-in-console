#ifndef PICTURE_H
#define PICTURE_H

#include <string>

#include "mgtv_library.h"

using std::string;
using mgtv_library::console::COLOR;


namespace pong_in_console
{
	struct PICTURE
	{
		string picture;
		COLOR color;
	};
}

#endif // !PICTURE_H
