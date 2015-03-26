#include "stdafx.h"
#include "DebugCursor.h"
#include "InputHandler.hpp"

DebugCursor::DebugCursor(void)
{
}


DebugCursor::~DebugCursor(void)
{
}

void DebugCursor::init()
{
	cursorPos = sf::Vector2i(0,0);
}

void DebugCursor::update()
{
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Right))
	{
		if (!isOdd(cursorPos.x+1) && !isOdd(cursorPos.y))
		{
			//do nothing
		}
		else
		{
			cursorPos.x += 1;
		}
	}
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Left))
	{
		if (!isOdd(cursorPos.x-1) && !isOdd(cursorPos.y))
		{
			//do nothing
		}
		else
		{
			cursorPos.x -= 1;
		}
	}
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Up))
	{
		if (!isOdd(cursorPos.x) && !isOdd(cursorPos.y-1))
		{
			//do nothing
		}
		else
		{
			cursorPos.y -= 1;
		}
	}
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Down))
	{
		if (!isOdd(cursorPos.x) && !isOdd(cursorPos.y+1))
		{
			//do nothing
		}
		else
		{
			cursorPos.y += 1;
		}
	}
	constrainPosition();
	setGridPos(cursorPos);
	_transform.setPosition(glm::vec3(3+(cursorPos.x*3), 2, 3+(cursorPos.y*3)));
}

sf::Vector2i DebugCursor::getCursorPos()
{
	return cursorPos;
}

void DebugCursor::setCursorPos(sf::Vector2i c)
{
	cursorPos = c;
}

void DebugCursor::setCursorPos(int x, int y)
{
	cursorPos = sf::Vector2i(x, y);
}

void DebugCursor::constrainPosition()
{
	if(cursorPos.x > 14)
	{
		cursorPos.x = 14;
	}
	if(cursorPos.x < 0)
	{
		cursorPos.x = 0;
	}
		if(cursorPos.y > 14)
	{
		cursorPos.y = 14;
	}
	if(cursorPos.y < 0)
	{
		cursorPos.y = 0;
	}
}