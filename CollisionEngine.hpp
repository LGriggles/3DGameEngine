#ifndef COLLISIONENGINE_HPP
#define COLLISIONENGINE_HPP

#include "Actor.hpp"
#include <iostream>

class CollisionEngine
{
public:
	std::vector<Actor*> _returnedCollider;
	std::vector<Actor*> _colliders;

    bool checkIfColliding(Actor& actorOne, Actor& actorTwo);
	std::vector<Actor*>* getActorPlaceFree(Actor* testMe, float x, float y, float z);
};



#endif