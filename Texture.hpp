#ifndef TEXTURE_HPP
#define TEXTURE_HPP

//C++
#include <string>
using std::string;
//SFML
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

/*! A texture */
class Texture {
private:
	sf::Image	_image;		//!< SFML Image bitmap loader
	GLuint		_texture;	//!< The texture handle for OpenGL
public:
	void init(string texturePath);					//!< Initialize the texture
	void GenerateTexture();							//!< OpenGL generate texture
	GLuint getTextureHandle() { return _texture; }; //!< Get texture OpenGL handle
};

#endif // !TEXTURE_HPP
