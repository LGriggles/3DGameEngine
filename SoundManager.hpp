#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

//C++
#include <string>
#include <vector>
using std::string;
using std::vector;

//SFML
#include <SFML\Audio.hpp>

class SoundManager
{
private:
	vector<sf::Sound*> _soundList;			//!< List of cached playable sounds
	vector<sf::SoundBuffer*> _soundBuffers;	//!< List of cached sound buffers that load in the sound
public:
	int loadSound(string path);			//!< Loads a sound in and returns an index of the sound to be used later for playback
	void playSound(int soundIndex);		//!< Play the sound using the index
};


#endif // !SOUNDMANAGER_HPP
