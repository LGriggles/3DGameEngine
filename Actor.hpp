#ifndef ACTOR_HPP
#define ACTOR_HPP

//GLM
#include <glm.hpp>

//3DGameEngine
#include "DrawingInstance.hpp"
#include "Transform.hpp"

/*! The base object that all game objects derive from */
class Actor
{
public:
	Transform		_transform;			//!< The transform of the gameobject, defines position rotatation scale etc
	DrawingInstance drawingInstance;	//!< Handles the drawing of the game object, represents the game object visually

	virtual void init();				//!< Called by the scene to initialize the object when it is created, override this to define the behaviour
	virtual void update();				//!< Called by the scene override this to define the behaviour of the object for updating
};
#endif // !GAMEOBJECT_H
