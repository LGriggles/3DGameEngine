#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

//3DGameEngine
#include "KeyboardInput.hpp"
#include "MouseInput.hpp"
#include "EngineGlobals.hpp"
/*! Engine input holds objects that manipulate input data */
namespace EngineInput
{
	extern KeyboardInput keyboardInput;	//!< Handles input of the keyboard
	extern MouseInput mouseInput;		//!< Handles input of the mouse
	extern EngineGlobals engineGlobals;
};

#endif // !INPUTHANDLER_HPP
