#pragma once

#include "Actor.hpp"

class DebugCursor : public Actor
{
private:
	sf::Vector2i cursorPos;
	void constrainPosition();

public:
	
	void init();			//!< Initializer
	void update();			//!< Update the object
	
	sf::Vector2i getCursorPos();
	void setCursorPos(sf::Vector2i);
	void setCursorPos(int x, int y);

	bool isOdd( int integer )
	{

		if ( integer % 2== 0 )
			return true;
		else
			return false;
	}

	DebugCursor(void);
	~DebugCursor(void);
};
