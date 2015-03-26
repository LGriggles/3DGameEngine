#ifndef DESTROYABLEBLOCK_HPP
#define DESTROYABLEBLOCK_HPP
#include "Actor.hpp"

class DestroyabeBlock : public Actor {
public:
	enum BlockState
	{
		NORMAL,
		DESTROYING,
		DESTROYED,
	};
	BlockState _blockState;

	glm::vec3 _teleportEndPosition;
		float _jumpAmount;		//!< Amount to jump by
	float _gravity;			//!< The object's gravity

	void init();			//!< Initializer
	void update();			//!< Update the object

	DestroyabeBlock(void);
	~DestroyabeBlock(void);
	void destroyed();

};



#endif