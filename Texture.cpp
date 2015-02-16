//3DGameEngine
#include "stdafx.h"
#include "Texture.hpp"

//SFML
#include <SFML\OpenGL.hpp>

void Texture::init(string texturePath)
{
	_image.loadFromFile(texturePath);
}

void Texture::GenerateTexture()
{
	glGenTextures(1, &_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //If the uvs go over 0 - 1 then repeat the image
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, _texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _image.getSize().x, _image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,_image.getPixelsPtr());
}