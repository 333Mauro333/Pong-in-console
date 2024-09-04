#ifndef LIMITED_ELEMENT_H
#define LIMITED_ELEMENT_H

#include "game_object/frame/frame.h"


namespace pong_in_console
{
	class LimitedElement
	{
	public:
		virtual ~LimitedElement();

		virtual void setMovementLimits(Frame* frame) = 0;
	};
}

#endif // !LIMITED_ELEMENT_H
