#include "stdafx.h"

#include "Mesh.hpp"

#include <iostream>


void Mesh::init()
{
}

void Mesh::generateMesh()
{
	//Generate vertex object buffers
	glGenVertexArrays(1, &VAOHandle);
	glGenBuffers(1, &_vertexBuffer);
	glGenBuffers(1, &_textureBuffer);
	glGenBuffers(1, &_normalsBuffer);
	glGenBuffers(1, &_indicesBuffer);

	glBindVertexArray(VAOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 3 * sizeof(float), 0);

	glEnableVertexAttribArray(0);  //Vertex positions
	glBufferData(GL_ARRAY_BUFFER, (_vertices.size() * 3) * sizeof(float), &_vertices[0].x, GL_STATIC_DRAW);
	
	if(_textureUVs.size() <= 0)
	{
		_textureUVs.push_back(sf::Vector2f(0,0));
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, _textureBuffer); //Texture UVs
	glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, 2 * sizeof(int), 0);

	glBufferData(GL_ARRAY_BUFFER, (_textureUVs.size() * 2) * sizeof(float), &_textureUVs[0].x, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	if(_vertNorms.size() <= 0)
	{
		_vertNorms.push_back(sf::Vector3f(0,0,0));
	}
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, (_vertNorms.size() * 3) * sizeof(float), &_vertNorms[0].x, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);  //vert normals
	glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, 3*sizeof(float), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBuffer); //Indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  _indices.size() * sizeof(int) * 3, &_indices[0].x,GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

std::vector<sf::Vector3i>* Mesh::getIndices()
{
	return &_indices;
}

GLuint Mesh::getVAO()
{
	return VAOHandle;
}

glm::mat4& Mesh::getMatrix()
{
	return _modelMatrix;
}

void Mesh::setVerts(vector<sf::Vector3f>& vertices)
{
	_vertices = vertices;
}
void Mesh::setIndices(vector<sf::Vector3i>& indices)
{
	_indices = indices;
}

void Mesh::setUVs(vector<sf::Vector2f>& UVs)
{
	_textureUVs = UVs;
}

void Mesh::setNorms(vector<sf::Vector3f>& normals)
{
	_vertNorms = normals;
}

std::vector<sf::Vector3f>* Mesh::getVertices()
{
	return &_vertices;
}

void Mesh::Draw()
{
	glBindVertexArray(getVAO());
	glDrawElements(GL_TRIANGLES, getIndices()->size() * 3, GL_UNSIGNED_INT, 0);
}