#include "stdafx.h"

#include "Actor.hpp"

void Actor::init()
{
	_transform._rotation.x=0.f;
	_transform._rotation.y=0.f;
	_transform._rotation.z=0.f;
}

void Actor::update()
{

}

bool Actor::isGridLocked()
{
	return _gridLocked;
}

sf::Vector2i Actor::getGridPos()
{
	return _gridPos;
}

CollisionEngine& Actor::getCollisionEngine()
{
	return *_collisionEngine;
}