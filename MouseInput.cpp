#include "stdafx.h"
#include "MouseInput.hpp"

void MouseInput::updateMousePosition(sf::Vector2i mousePos)
{
	_mousePosition = mousePos;
}

void MouseInput::setMousePosition(sf::Vector2i mousePos)
{
	sf::Mouse::setPosition(mousePos,*_renderWindow);
	_mousePosition = mousePos;
}

sf::Vector2i MouseInput::getMousePosition()
{
	return _mousePosition;
}