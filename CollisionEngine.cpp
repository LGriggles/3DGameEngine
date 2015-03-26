#include "CollisionEngine.hpp"
#include <iostream>


    bool CollisionEngine::checkIfColliding(Actor& actorOne, Actor& actorTwo)
    {
        //Calculate the sides of rect A
		float leftA			= actorOne._transform._position.x;
        float rightA		= actorOne._transform._position.x + actorOne._collision._width;
		float topA			= actorOne._transform._position.z;
		float bottomA		= actorOne._transform._position.z + actorOne._collision._length;
		float depthTopA		= actorOne._transform._position.y;
		float depthBottomA	= actorOne._transform._position.y + actorOne._collision._depth;

        //Calculate the sides of rect B
		float leftB			= actorTwo._transform._position.x;
        float rightB		= actorTwo._transform._position.x + actorTwo._collision._width;
        float topB			= actorTwo._transform._position.z;
        float bottomB		= actorTwo._transform._position.z + actorTwo._collision._length;
		float depthTopB		= actorTwo._transform._position.y;
		float depthBottomB	= actorTwo._transform._position.y + actorTwo._collision._depth;
		

        if(bottomA <= topB)
        {
            return false;
        }

        if(topA >= bottomB)
        {
            return false;
        }

        if(rightA <= leftB)
        {
            return false;
        }

        if(leftA >= rightB)
        {
            return false;
        }

		if(depthBottomA <= depthTopB)
        {
            return false;
        }

        if(depthTopA >= depthBottomB)
        {
            return false;
        }

        return true;
    }

	std::vector<Actor*>* CollisionEngine::getActorPlaceFree(Actor* testMe, float x, float y, float z)
    {
		float previousX = testMe->_transform._position.x;
        float previousY = testMe->_transform._position.y;
		float previousZ = testMe->_transform._position.z;

		testMe->_transform.setPosition(glm::vec3(x,z,y));

        for (int i = 0; i < _colliders.size(); i++)
        {
			if (_colliders.at(i)->_collision.isActive){
			if (checkIfColliding(*testMe, *_colliders.at(i)))
            {
				if(testMe != _colliders.at(i))
				{
					testMe->_transform.setPosition(glm::vec3(previousX,previousY,previousZ));
					_returnedCollider.push_back(_colliders.at(i));
				}
            }
			}
        }
		if(_returnedCollider.size() > 0)
		{
			return &_returnedCollider;
		}
        testMe->_transform.setPosition(glm::vec3(previousX,previousY,previousZ));
        return 0;
    }


