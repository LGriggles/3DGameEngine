#include "stdafx.h"
#include "RacingCar.h"
#include "InputHandler.hpp"
#include "CollisionEngine.hpp"
#include "Scene.hpp"
#include "ActorList.hpp"
#include "Bomb.hpp"

RacingCar::RacingCar(void)
{
}

RacingCar::~RacingCar(void)
{
}

void RacingCar::init()
{
	_playerDirection = PlayerDirection::RIGHT;
	_velocityX = 0;
	_velocityY = 0;
	_playerState = PlayerState::NORMAL;
	_gravity = 0;
	_velocityX = 16;
	_velocityZ = 16;
	_playerGravity = PlayerGravity::GROUNDED;
	_playerBounce = PlayerBounce::DONE;
}

void RacingCar::update()
{
	switch(_playerState)
	{
	case PlayerState::NORMAL:
		{	
			

			switch(_playerGravity)
			{
			case PlayerGravity::GROUNDED:

				break;

			case PlayerGravity::JUMPING:
				{
					_gravity = 0;
					_transform.setPosition(_transform._position + glm::vec3(0,(_jumpPower * 0.1f),0));

					if(_jumpPower > 0)
					{
						_jumpPower --;
					}
					else
					{
						_jumpPower = 0;
						_gravity = 0;
						_playerGravity = PlayerGravity::FALLING;
					}
				}
				break;

			case PlayerGravity::FALLING:
				{
					if(_gravity < 12)
					{
						_gravity ++;
					}
					std::vector<Actor*>* _velocityCollidersY = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.y + ((_gravity+4) * 0.1f)*-1,this->_transform._position.z);
					if(_velocityCollidersY != 0)
					{
						_playerGravity = PlayerGravity::GROUNDED;
						glm::vec3 newPos = (*_velocityCollidersY).at(0)->_transform._position;
						newPos.x = _transform._position.x;
						newPos.y += 2;
						newPos.z = _transform._position.z;
						_transform.setPosition(newPos);
					}
					else
					{
						_transform.setPosition(_transform._position + glm::vec3(0,(_gravity * 0.1f)*-1,0));
					}
				}
				break;
			}
			//{
			//	std::vector<Actor*>* _velocityCollidersX = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + _velocityX * 0.1f,this->_transform._position.z,this->_transform._position.y);
			//	if(_velocityCollidersX != 0)
			//	{
			//	}
			//	else
			//	{
			//		//_transform.setPosition(_transform._position + glm::vec3(_velocityX * 0.1f,0,0));
			//	}
			//	std::vector<Actor*>* _velocityCollidersZ = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z+ _velocityZ * 0.1f,this->_transform._position.y);
			//	if(_velocityCollidersZ != 0)
			//	{
			//	}
			//	else
			//	{
			//		//_transform.setPosition(_transform._position + glm::vec3(0,0,_velocityZ * 0.1f));
			//	}
			//	std::vector<Actor*>* _velocityCollidersY = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z,this->_transform._position.y + _velocityY * 0.1f);
			//	if(_velocityCollidersY != 0)
			//	{
			//	}
			//	else
			//	{
			//		//_transform.setPosition(_transform._position + glm::vec3(0,_velocityY * 0.1f,0));
			//	}
			//}


			//if(_velocityX > 0)
			//{
			//	_velocityX -=0.5f;
			//}

			//if(_velocityX < 0)
			//{
			//	_velocityX +=0.5f;
			//}

			//if(_velocityY > -5)
			//{
			//	_velocityY -= 0.5f;
			//}

			//if(_velocityY < -5)
			//{
			//	_velocityY +=0.5f;
			//}

			//if(_velocityZ > 0)
			//{
			//	_velocityZ -=0.5f;
			//}

			//if(_velocityZ < 0)
			//{
			//	_velocityZ +=0.5f;
			//}

			glm::vec3 temp = _moveTo;
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Up))
			{
				//_transform.rotate(glm::vec3(0,3,0));

				_moveTo = _transform._position + glm::vec3(0,0,-3);

				int xSnap, ySnap, zSnap;
				xSnap = _moveTo.x / 3;
				ySnap = _transform._position.y;
				zSnap = _moveTo.z / 3;

				glm::vec3 snapPos(xSnap*3,_transform._position.y,zSnap*3);
				_moveTo = snapPos;

				std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,
					_moveTo.x,
					_moveTo.y,
					_moveTo.z);
				if(_actorsReturned != 0)
				{
					_moveTo = temp;
				}
				//else
				{
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Right))
			{
				/*std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + 0.1f,this->_transform._position.z,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}*/
				{

					//_transform.rotate(glm::vec3(0,3,0));
					_moveTo = _transform._position + glm::vec3(3,0,0);

					int xSnap, ySnap, zSnap;
					xSnap = _moveTo.x / 3;
					ySnap = _transform._position.y;
					zSnap = _moveTo.z / 3;

					glm::vec3 snapPos(xSnap*3,_transform._position.y,zSnap*3);
					_moveTo = snapPos;

					std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,
						_moveTo.x,
						_moveTo.y,
						_moveTo.z);
					if(_actorsReturned != 0)
					{
						_moveTo = temp;
					}
					//_transform.setPosition(_moveTo);
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Down))
			{
				/*std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.z + 0.1f,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else*/
				{
					//_transform.rotate(glm::vec3(0,3,0));
					//_transform.setPosition(_transform._position + glm::vec3(0,0,3));

					_moveTo = _transform._position + glm::vec3(0,0,3);

					int xSnap, ySnap, zSnap;
					xSnap = _moveTo.x / 3;
					ySnap = _transform._position.y;
					zSnap = _moveTo.z / 3;

					glm::vec3 snapPos(xSnap*3,_transform._position.y,zSnap*3);
					_moveTo = snapPos;

					std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,
						_moveTo.x,
						_moveTo.y,
						_moveTo.z);
					if(_actorsReturned != 0)
					{
						_moveTo = temp;
					}
					//_transform.setPosition(snapPos);
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::Left))
			{
				/*std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x - 0.1f,this->_transform._position.z,this->_transform._position.y);
				if(_actorsReturned != 0)
				{
				}
				else*/
				{
					//_transform.rotate(glm::vec3(0,3,0));
					//_transform.setPosition(_transform._position + glm::vec3(-3,0,0));

					_moveTo = _transform._position + glm::vec3(-3,0,0);

					int xSnap, ySnap, zSnap;
					xSnap = _moveTo.x / 3;
					ySnap = _transform._position.y;
					zSnap = _moveTo.z / 3;

					glm::vec3 snapPos(xSnap*3,_transform._position.y,zSnap*3);
					_moveTo = snapPos;

					std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,
						_moveTo.x,
						_moveTo.y,
						_moveTo.z);
					if(_actorsReturned != 0)
					{
						_moveTo = temp;
					}
					//_transform.setPosition(snapPos);
				}
			}
			if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::F))
			{
				switch(_playerDirection)
				{
				case PlayerDirection::RIGHT:
					Bomb* _myBomb = &(Bomb&)_gameScene->createActor(_transform._position,ActorTypes::BOMB);
					_myBomb->_transform.setPosition(_transform._position + glm::vec3(1,0,0));
					int xSnap, ySnap, zSnap;
					xSnap = _transform._position.x / 3;
					ySnap = _transform._position.y / 3;
					zSnap = _transform._position.z / 3;

					_myBomb->_transform._position.x = xSnap * 3;
					_myBomb->_transform._position.y = _transform._position.y + 1;
					_myBomb->_transform._position.z = zSnap * 3;
					break;
				}
			}
			if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::N))
			{

				//_playerState = PlayerState::TELEPORTATION;
			}
			//std::vector<Actor*>* _actorsReturned = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + 0.1f,this->_transform._position.z,this->_transform._position.y);
			//if(_actorsReturned != 0)
			//{
			//}
			//else)
			{
				switch(_playerBounce)
				{
				case PlayerBounce::DONE:
					if(Transform::distance(_moveTo,_transform._position) > 0.1f)
					{
						_playerBounce = PlayerBounce::BOUNCE;
					}

					break;

				case PlayerBounce::BOUNCE:
					if(_playerGravity == PlayerGravity::GROUNDED)
			{
				_jumpPower = 4;
				_playerGravity = PlayerGravity::JUMPING;
			}

					if(Transform::distance(_moveTo,_transform._position) > 0.1f)
					{
						_transform.setPosition(_transform._position + (Transform::vectorToward(_moveTo,_transform._position) * 0.1f));
					}
					else
					{
						_transform.setPosition(_moveTo);
						_moveTo = _transform._position;
						_playerBounce = PlayerBounce::DONE;
						break;
					}
				}
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