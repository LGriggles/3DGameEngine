#include "stdafx.h"

#include "SoundManager.hpp"


int SoundManager::loadSound(string path)
{
	sf::SoundBuffer *buffer = new sf::SoundBuffer();
	_soundBuffers.push_back(buffer);
    if (!buffer->loadFromFile(path))
	{
        return -1;
	}
	sf::Sound* newSound = new sf::Sound(*buffer);
	newSound->setVolume(30);
	_soundList.push_back(newSound);
	return _soundList.size()-1;	//Return the index
}

void SoundManager::playSound(int soundIndex)
{
	_soundList.at(soundIndex)->play();
}