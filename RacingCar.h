#pragma once

#include "Actor.hpp"

class RacingCar : public Actor
{
public:
	enum PlayerState
	{
		TELEPORTATION,
		NORMAL,
		TELEPORTATIONEND,
	};
	PlayerState _playerState;

	glm::vec3 _teleportEndPosition;
		float _jumpAmount;		//!< Amount to jump by
	float _gravity;			//!< The object's gravity

	void init();			//!< Initializer
	void update();			//!< Update the object

	RacingCar(void);
	~RacingCar(void);
};

