#include "stdafx.h"
#include "RacingCar.h"
#include "InputHandler.hpp"
#include "CollisionEngine.hpp"
#include "Scene.hpp"

RacingCar::RacingCar(void)
{
}

RacingCar::~RacingCar(void)
{
}

void RacingCar::init()
{
	_velocityX = 0;
	_velocityY = 0;
	_playerState = PlayerState::NORMAL;
	_gravity = 5;
	_velocityX = 16;
	_velocityZ = 16;
}

void RacingCar::update()
{
	switch(_playerState)
	{
	case PlayerState::NORMAL:
		{
			{
				std::vector<Actor*>* _velocityCollidersX = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + _velocityX * 0.1f,this->_transform._position.z,this->_transform._position.y);
				if(_velocityCollidersX != 0)
				{
				}
				else
				{
					_transform.setPosition(_transform._position + glm::vec3(_velocityX * 0.1f,0,0));
				}
				std::vector<Actor*>* _velocityCollidersZ = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z+ _velocityZ * 0.1f,this->_transform._position.y);
				if(_velocityCollidersZ != 0)
				{
				}
				else
				{
					_transform.setPosition(_transform._position + glm::vec3(0,0,_velocityZ * 0.1f));
				}
				std::vector<Actor*>* _velocityCollidersY = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z,this->_transform._position.y + _velocityY * 0.1f);
				if(_velocityCollidersY != 0)
				{
				}
				else
				{
					_transform.setPosition(_transform._position + glm::vec3(0,_velocityY * 0.1f,0));
				}
			}


			if(_velocityX > 0)
			{
				_velocityX -=0.5f;
			}

			if(_velocityX < 0)
			{
				_velocityX +=0.5f;
			}

			if(_velocityY > -5)
			{
				_velocityY -= 0.5f;
			}

			if(_velocityY < -5)
			{
				_velocityY +=0.5f;
			}

			if(_velocityZ > 0)
			{
				_velocityZ -=0.5f;
			}

			if(_velocityZ < 0)
			{
				_velocityZ +=0.5f;
			}
			//_transform.setScale(Transform::lerp(glm::vec3(0,0,0),_transform._scale,20.5f));
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Up))
			{
				std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z - 0.1f,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else
				{
					_transform.rotate(glm::vec3(0,3,0));
					_transform.setPosition(_transform._position + glm::vec3(0,0,-0.2f));
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Right))
			{

				std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + 0.1f,this->_transform._position.z,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else
				{
					_transform.rotate(glm::vec3(0,1.5f,0));
					_transform.setPosition(_transform._position + glm::vec3(0.2f,0,0.0f));
				}	
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Down))
			{
				std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z + 0.1f,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else
				{
					_transform.rotate(glm::vec3(0,0.0f,0));
					_transform.setPosition(_transform._position + glm::vec3(0,0,0.2f));
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Left))
			{
				std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x - 0.1f,this->_transform._position.z,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else
				{
					_transform.rotate(glm::vec3(0,4.5f,0));
					_transform.setPosition(_transform._position + glm::vec3(-0.2f,0,0.0f));
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::N))
			{
				_playerState = PlayerState::TELEPORTATION;
			}
		}
		break;

	case PlayerState::TELEPORTATION:
		_transform.setPosition(_transform._position + Transform::vectorToward(_teleportEndPosition,_transform._position));
		_transform.setScale(Transform::lerp(glm::vec3(0.0f,4,0.0f),_transform._scale,0.09f));
		if(_transform._scale.x > -0.9 && _transform._scale.y > 3.9 && _transform._scale.z > -0.9)
		{
			if(_transform._scale.x < 0.1 && _transform._scale.y < 4.1 && _transform._scale.z < 0.1)
			{
				_transform.setPosition(_teleportEndPosition);
				_playerState = PlayerState::TELEPORTATIONEND;
			}
		}
		break;
	case PlayerState::TELEPORTATIONEND:
		_transform.setScale(Transform::lerp(glm::vec3(1,1,1),_transform._scale,0.09f));
		if(_transform._scale.x > 0.9 && _transform._scale.y > 0.9 && _transform._scale.z > 0.9)
		{
			if(_transform._scale.x < 1.1 && _transform._scale.y < 1.1 && _transform._scale.z < 1.1)
			{
				_playerState = PlayerState::NORMAL;
			}
		}
		break;
	}
}