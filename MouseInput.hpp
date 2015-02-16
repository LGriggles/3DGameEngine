#ifndef MOUSEINPUT_HPP
#define MOUSEINPUT_HPP

//SFML
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

/*! Handles mouse input*/
class MouseInput
{
protected:
	friend class GraphicsRenderer;

	sf::RenderWindow*	_renderWindow;					//!< The main render window, used for setting mouse position
	sf::Vector2i		_mousePosition;					//!< The mouse's current position
public:
	void			updateMousePosition(sf::Vector2i mousePos);
	void			setMousePosition(sf::Vector2i mousePos);
	sf::Vector2i	getMousePosition();
};

#endif // !MOUSEINPUT
