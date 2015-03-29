#include "Bomb.hpp"
#include "CollisionEngine.hpp"

void Bomb::init()
{
	_velocityX = 12;
	_velocityY = 0;
	_velocityZ = 0;
	_collision._depth = 1;
	_collision._width = 1;
	_collision._length = 1;
	_collision.isActive = true;
	flash = -1;
}

void Bomb::update()
{
	_myTint.x -= 0.01f;
	std::vector<Actor*>* _velocityCollidersX = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x + _velocityX * 0.1f,this->_transform._position.y,this->_transform._position.z);
	if(_velocityCollidersX != 0)
	{
	}
	else
	{
		_transform.setPosition(_transform._position + glm::vec3(_velocityX * 0.1f,0,0));
	}
	std::vector<Actor*>* _velocityCollidersZ = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.y,this->_transform._position.z+ _velocityZ * 0.1f);
	if(_velocityCollidersZ != 0)
	{
	}
	else
	{
		_transform.setPosition(_transform._position + glm::vec3(0,0,_velocityZ * 0.1f));
	}
	std::vector<Actor*>* _velocityCollidersY = getCollisionEngine().getActorPlaceFree(this,this->_transform._position.x,this->_transform._position.y + _velocityY * 0.1f,this->_transform._position.z);
	if(_velocityCollidersY != 0)
	{
	}
	else
	{
		_transform.setPosition(_transform._position + glm::vec3(0,_velocityY * 0.1f,0));
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

}