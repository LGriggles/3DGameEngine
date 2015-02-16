#include "stdafx.h"

#include "Transform.hpp"

Transform::Transform()
{
	_up			= glm::vec3(0,-1,0);
	_forward	= glm::vec3(0,0,1);
	_right		= glm::cross(_up,_forward);
	_position	= glm::vec3(0,0,0);
	_rotation	= glm::vec3(0,0,0);
	_scale		= glm::vec3(1,1,1);
	doAlookAt	= false;
}

void Transform::lookAt(glm::vec3 position)
{
	doAlookAt = true;
	_target = position;
}

void Transform::translate(glm::vec3 position)
{
	_position = _position + position;
}

void Transform::translateForward(float amount)
{
	_position += _forward;
}

void Transform::setPosition(glm::vec3 position)
{
	_position = position;
}

void Transform::rotate(glm::vec3 rotation)
{
	_rotation	= _rotation + glm::vec3(rotation.x,rotation.y,rotation.z);
	_forward.x	= cos(_rotation.x) * _forward.x;
	_forward.y	= sin(_rotation.y) * _forward.y;

	_right		= glm::cross(_up,_forward);
	_up			= glm::normalize(glm::cross(_forward,_right));
}

void Transform::rotateToward(glm::vec3 position)
{
	
}

void Transform::setScale(glm::vec3 scale)
{
	_scale = scale;
}

glm::mat4 Transform::getTransMatrix()
{
	_transformationMatrix = glm::mat4x4();
	_transformationMatrix += glm::translate(_transformationMatrix,_position);
	_transformationMatrix += glm::scale(_scale);
	if(doAlookAt)
	{
		doAlookAt = false;
	}
	return _transformationMatrix;
}

Transform::~Transform()
{
}