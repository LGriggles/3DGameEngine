#include "stdafx.h"
#include "RacingCar.h"
#include "InputHandler.hpp"

RacingCar::RacingCar(void)
{
}


RacingCar::~RacingCar(void)
{
}

void RacingCar::init()
{
	_gravity = 5;
}

void RacingCar::update()
{
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Right))
	{
		//Turn right
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Left))
	{
		_transform.rotate(glm::vec3(90,0,0));
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Space))
	{
		_transform.translateForward(5);
	}

	if(_jumpAmount > 0) //Do jump
	{
		_transform.translate(glm::vec3(0,_jumpAmount*0.01f,0));
		_jumpAmount -=0.5f;
	}

	if(_transform._position.y < 0.5f) //On the ground do nothing
	{
		_jumpAmount = 20;
	}
	else //Off the ground do gravity
	{
		_transform.translate(glm::vec3(0,-_gravity*0.01f,0));
	}
}
