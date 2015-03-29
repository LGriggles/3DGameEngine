#pragma once

#include "Actor.hpp"

class RacingCar : public Actor
{
public:
	enum PlayerDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	PlayerDirection _playerDirection;
	glm::vec3 _moveTo;

	enum PlayerGravity
	{
		GROUNDED,
		FALLING,
		JUMPING,
	};
	PlayerGravity _playerGravity;
	float _gravity;
	float _jumpPower;


	enum PlayerState
	{
		TELEPORTATION,
		NORMAL,
		TELEPORTATIONEND,
	};
	PlayerState _playerState;

	enum PlayerBounce
	{
		BOUNCE,
		DONE
	};
	PlayerBounce _playerBounce;

	glm::vec3 _teleportEndPosition;

	void init();			//!< Initializer
	void update();			//!< Update the object

	RacingCar(void);
	~RacingCar(void);
};

