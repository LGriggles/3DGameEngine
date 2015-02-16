#ifndef JUMPINGOBJECT_HPP
#define JUMPINGOBJECT_HPP

//GLM
#include <glm.hpp>
//3DGameEngine
#include "Actor.hpp"

/*! A demonstration of the engine's GameObject, shows how behaviours can be specified (for example of a player) */
class JumpingObject: public Actor
{
public:
	float _jumpAmount;		//!< Amount to jump by
	float _gravity;			//!< The object's gravity
	
	void init();			//!< Initializer
	void update();			//!< Update the object
};

#endif // !JUMPINGOBJECT_HPP
