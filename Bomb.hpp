#ifndef BOMB_HPP
#define BOMB_HPP

#include "Actor.hpp"

class Bomb : public Actor
{
public:
	float flash;
	void init();			//!< Initializer
	void update();			//!< Update the object
};


#endif