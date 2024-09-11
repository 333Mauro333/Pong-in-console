#include "game_object.h"

#include <iostream>

#include "mgtv_library.h"

using std::cout;
using mgtv_library::console::ConsoleExt;


namespace pong_in_console
{
	GameObject::GameObject(int x, int y)
	{
		previousPosition = { x, y };

		position = { x, y };
		size = { 1, 1 };
		isActive = true;
	}
	GameObject::GameObject(int x, int y, int w, int h)
	{
		previousPosition = { x, y };

		position = { x, y };
		size = { w, h };
		isActive = true;
	}
	GameObject::~GameObject()
	{

	}

	void GameObject::erase()
	{
		if (previousPosition.x != position.x || previousPosition.y != position.y)
		{
			for (int i = 0; i < size.h; i++)
			{
				ConsoleExt::goToCoordinates(previousPosition.x, previousPosition.y);

				for (int j = 0; j < size.w; j++)
				{
					cout << " ";
				}
			}
		}
	}

	void GameObject::activate()
	{
		isActive = true;
	}
	void GameObject::deactivate()
	{
		isActive = false;
		
		ConsoleExt::goToCoordinates(position.x, position.y);
		cout << " ";
	}

	bool GameObject::getIsActive()
	{
		return isActive;
	}
	POSITION GameObject::getPosition()
	{
		return position;
	}
	SIZE GameObject::getSize()
	{
		return size;
	}
	int GameObject::getUp()
	{
		return position.y;
	}
	int GameObject::getDown()
	{
		return position.y + size.h - 1;
	}
	int GameObject::getLeft()
	{
		return position.x;
	}
	int GameObject::getRight()
	{
		return position.x + size.w - 1;
	}

	void GameObject::setPosition(POSITION position)
	{
		this->position = position;
	}
	void GameObject::setPosition(int x, int y)
	{
		position = { x, y };
	}
	void GameObject::setSize(SIZE size)
	{
		this->size = size;
	}
	void GameObject::setSize(int w, int h)
	{
		size = { w, h };
	}


	void GameObject::savePositionAsPrevious()
	{
		previousPosition = position;
	}
}
