#ifndef MESH_HPP
#define MESH_HPP

//C++
#include <vector>
using std::vector;
//GLM
#include <GL\glew.h>
#include <gtx\transform.hpp>
//SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
//3DGameEngine
#include "Texture.hpp"

/*! Holds model data */
class Mesh
{
public:
	void		init();	//!< Initialize the mesh
	void		Draw(); //!< Draw the mesh now, called between clear and display
	void						generateMesh();								//!< OpenGL generation
	std::vector<sf::Vector3i>*	getIndices();								//!< Get the indices
	GLuint						getVAO();									//!< Get the vertex array object
	glm::mat4&					getMatrix();								//!< Get the mesh's matrix
	std::vector<sf::Vector3f>*	getVertices();								//!< Get the vertices
	void						setVerts(vector<sf::Vector3f>& vertices);	//!< Set the vertices
	void						setIndices(vector<sf::Vector3i>& indices);	//!< Set the indices
	void						setUVs(vector<sf::Vector2f>& UVs);			//!< Set the texture UVs
	void						setNorms(vector<sf::Vector3f>& normals);	//!< Set the normals
	
private:
	glm::mat4	_modelMatrix;		//!< The matrix for the mesh
	GLuint		_modelMatrixID;		//!< The matrix's ID
	GLuint		VAOHandle;			//!< The vertex array object's handle in OpenGL
	GLuint		_myShaderHandle;	//!< The the currently used shader's handle for the mesh
	std::vector<sf::Vector2f>	_textureUVs;	//!< UVs for texture
	std::vector<sf::Vector3f>	_vertices;		//!< Verts for mesh
	vector<sf::Vector3f>		_vertNorms;		//!< Vertex normals
	std::vector<sf::Vector3i>	_indices;		//!< Indices
	GLuint _vertexBuffer;	//!< OpenGL vertex buffer handle
	GLuint _indicesBuffer;	//!< OpenGL Index buffer
	GLuint _textureBuffer;	//!< OpenGL Texture buffer
	GLuint _normalsBuffer;	//!< OpenGL Normals buffer
};
#endif