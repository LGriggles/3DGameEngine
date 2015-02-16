#include "stdafx.h"

#include "TestingGrounds.hpp"

void JumpingObject::init()
{
	_gravity = 5;
}

void JumpingObject::update()
{
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

