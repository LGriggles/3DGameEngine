#include "stdafx.h"

#include "Camera.hpp"


#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <glm.hpp>



void Camera::init()
{
	_position	= glm::vec3(1.5,1.0f,1.0f);
	_up			= glm::vec3(0.0f,1.0f,0.0f);
	_target		= _position + glm::vec3(0.0f,0.0f,-1.0f);
	_right		= glm::cross(_up,_target);
	_forward	= _target;

	_mView = glm::lookAt(_position, glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f));
	_mProj = glm::ortho(-12.0f, 12.0f, -12.0f, 12.0f, 0.0f, 20.0f);
	//_mProj = glm::perspective(90.0f, 1.0f, 0.0001f,100.0f);
}

void Camera::setPosition(const glm::vec3& position)
{
	_position	+= position;
	if(!_hasTarget)
	_target		+= position;
	else
		_target = *_targetPtr;

	complete();
}

void Camera::rotate(float x, float y)
{
	_target = _target - _position;

	_rotation = glm::rotate(_target,-x*0.002f,glm::vec3(0.f,1.f,0.f));
	_rotation = glm::rotate(_target,-y*0.002f,glm::vec3(1.f,0.f,0.f));
	_target = glm::rotate(_target,-x*0.002f,glm::vec3(0.f,1.f,0.f));
	_target = glm::rotate(_target,-y*0.002f,glm::vec3(1.f,0.f,0.f));

	_target = _target + _position;

	complete();
}

void Camera::complete()
{
	_forward		= _target - _position;
	_right			= glm::cross(_up,_forward);
	glm::vec3 up	= glm::normalize(glm::cross(_forward,_right));
	_mView			= glm::lookAt(_position,_target,up);
	if(_hasTarget)
	{
		_target = *_targetPtr;
	}
}

void Camera::StrafeRight(float speed)
{
	_target		-= _right *	speed;
	_position	-= _right * speed;
	complete();
}

void Camera::StrafeLeft(float speed)
{
	_target		+= _right * speed;
	_position	+= _right * speed;
	complete();
}

void Camera::GoForward(float speed)
{
	_position	+= _forward * speed;
	_target		+= _forward * speed;
	complete();
}

void Camera::GoBackward(float speed)
{
	_position	-= _forward * speed;
	_target		-= _forward * speed;
	complete();
}

void Camera::update()
{
	complete();
}

void Camera::prepareForDraw()
{
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &_mView[0][0]);
	glUniformMatrix4fv(_projectionMatrixID, 1, GL_FALSE, &_mProj[0][0]);
}