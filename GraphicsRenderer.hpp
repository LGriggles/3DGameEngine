#ifndef GRAPHICSRENDERER_HPP
#define GRAPHICSRENDERER_HPP

//3DGameEngine
#include "Scene.hpp"

enum RETURNVALUE
{
	CLOSE,
	RESTARTGRAPHICS,	NONE,
};

/*! The mediator between winapi and SFML */
class GraphicsRenderer
{
private:
	HWND*				_hwnd;				//!< WinAPI hwnd
	Scene				_scene;				//!< The scene
	sf::RenderWindow*	_myRenderWindow;	//!< The SFML render window
public:
	void				init(HWND& hwnd);						//!< Initializes, pass the HWND from winapi to the graphics renderer
	RETURNVALUE			update();								//!< Update the graphics renderer, called by 
	void				draw();									//!< Does the drawing
	void				winAPIinput(unsigned int callback);		//!< Windows API callbacks
};

#endif