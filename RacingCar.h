#pragma once

#include "Actor.hpp"

class RacingCar : public Actor
{
public:
	float _jumpAmount;		//!< Amount to jump by
	float _gravity;			//!< The object's gravity
	
	void init();			//!< Initializer
	void update();			//!< Update the object

	RacingCar(void);
	~RacingCar(void);
};

