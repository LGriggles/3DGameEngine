#include "stdafx.h"
#include "KeyboardInput.hpp"

//A key has now been pressed
void KeyboardInput::nowKeyPressed(int key)
{
	if(key >= 0)
	{
		_keyPressed[key] = true;
		_keyDown[key] = true;
		_keysPressed.push_back(key);
	}
}

//Has the key been released
void KeyboardInput::nowKeyReleased(int key)
{
	if(key >= 0)
	{
		_keyPressed[key] = false;
		_keyDown[key] = false;
		_keyReleased[key] = true;
		_keysReleased.push_back(key);
	}
}

//Has the key been pressed once
bool KeyboardInput::isKeyPressed(int key)
{
	return _keyPressed[key];
}

//Is a key currently being held
bool KeyboardInput::isKeyHeld(int key)
{
	return _keyDown[key];
}

//Turn pressed and released off
void KeyboardInput::update()
{
	for(auto it : _keysPressed)
	{
		_keyPressed[it] = false;
	}
	for(auto it : _keysReleased)
	{
		_keyReleased[it] = false;
	}
	_keysPressed.clear();
	_keysReleased.clear();
}


namespace InputHandler
{
	KeyboardInput keyboardInput;
}


