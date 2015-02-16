#include "stdafx.h"

//GLM
#include <GL\glew.h>

//SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

//3DGameEngine
#include "GraphicsRenderer.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "InputHandler.hpp"
#include "WinAPI.hpp"

void GraphicsRenderer::init(HWND& hwnd)
{
	_hwnd = &hwnd;
	//create the window
	sf::ContextSettings contextSettings(24,8);
	contextSettings.antialiasingLevel = 4;

	_myRenderWindow = new sf::RenderWindow(hwnd,contextSettings);
	_myRenderWindow->setVerticalSyncEnabled(false);
	_myRenderWindow->setFramerateLimit(60);
	_myRenderWindow->resetGLStates();

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

	//Enable lighting
    glEnable(GL_LIGHTING);
	// Bind the texture
    glEnable(GL_TEXTURE_2D);
	//Initialize glew
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	EngineInput::mouseInput._renderWindow = _myRenderWindow;
	_scene.init();
}


RETURNVALUE GraphicsRenderer::update()
{
	//handle events
	sf::Event event;
	while (_myRenderWindow->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::KeyPressed:
			EngineInput::keyboardInput.nowKeyPressed(event.key.code);
			break;

		case sf::Event::KeyReleased:
			EngineInput::keyboardInput.nowKeyReleased(event.key.code);
			break;

		case sf::Event::Resized:
			glViewport(0, 0, event.size.width, event.size.height);
			break;

		case sf::Event::MouseButtonPressed:
			if(event.mouseButton.button == sf::Mouse::Right)
			{
				WindowsAPIinterface::winAPIinterface.spawnContextMenu(sf::Mouse::getPosition(*_myRenderWindow));
			}
			break;
		}
	}

	//Update the mouse's position
	EngineInput::mouseInput.updateMousePosition(sf::Mouse::getPosition(*_myRenderWindow));

	//Draw the scene
	_scene.update();

	//Display the frame for SFML
	_myRenderWindow->display();

	//Finish up with keyboard
	EngineInput::keyboardInput.update();
	return RETURNVALUE::NONE;
}

void GraphicsRenderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_scene.draw();
}

void GraphicsRenderer::winAPIinput(unsigned int callback)
{
	_scene.winAPIinput(callback);
}