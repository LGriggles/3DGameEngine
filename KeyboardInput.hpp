#ifndef KEYBOARDINPUT_HPP
#define KEYBOARDINPUT_HPP
//C++
#include <vector>
using std::vector;
/*! Handles keyboard input */
class KeyboardInput
{
private:
	bool		_keyPressed[1024];	//!< Identifies the keys that have been pressed in the current loop
	vector<int> _keysPressed;		//!< Contains which keys have been pressed this loop, used to release after
	bool		_keyDown[1024];		//!< Identifies which keys are being held down currently
	bool		_keyReleased[1024];	//!< Identifies which keys have been released this loop
	vector<int> _keysReleased;		//!< Holds an index to later stop the release
public:
	void nowKeyPressed(int key);	//!< A key has now been pressed, called by the 3D game engine
	void nowKeyReleased(int key);	//!< A key has new been released, called by the 3D game engine
	bool isKeyPressed(int key);		//!< A check, returns true if the key has been pressed in the loop
	bool isKeyHeld(int key);		//!< A check, returns true if the key is currently being held
	void update();					//!< Update, handles keys pressed and other miscaelenous keyboard functionality
};
#endif // !KEYBOARDINPUT_HPP
