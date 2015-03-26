#ifndef DRAWINGINSTANCE_HPP
#define DRAWINGINSTANCE_HPP

//3DGameEngine
#include "Mesh.hpp"

/*! A drawing instance, an individual object that can be drawn */
class DrawingInstance
{
private:
	Mesh*		_myMesh;		//!< Pointer to this drawing instance's mesh
	bool		_hasMesh;		//!< Results true if the drawing instance has a mesh
	Texture*	_myTexture;		//!< Pointer to the texture for the drawing instance
	bool		_hasTexture;	//!< Results true if the drawing instance has a texture
	GLuint		_myShaderID;	//!< The GLuint identifier of the shader program
public:
				DrawingInstance();
	Texture&	getTexture();								//!< Get the address of the texture
	void		giveMesh(Mesh &_newMesh);					//!< Give this drawing instance a mesh
	void		setHasMesh(bool m){
		_hasMesh = m;
	}
	Mesh&		getMesh();									//!< Get this drawing instance's mesh
	GLuint		getMyShader();								//!< Get the shader identifier
	void		setMyShader(GLuint _ShaderID);				//!< Set my shader
	void		giveTexture(Texture& giveThis);				//!< Give me a texture
	bool		hasMesh() { return _hasMesh; };				//!< Returns true if there is a mesh set
	bool		hasTexture() { return _hasTexture; };		//!< Returns true if there is a texture set
};

#endif