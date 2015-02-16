#include "stdafx.h"

#include "DrawingInstance.hpp"

void DrawingInstance::giveMesh(Mesh &_newMesh)
{
	_hasMesh = true;
	_myMesh = &_newMesh;
}
Mesh& DrawingInstance::getMesh()
{
	return *_myMesh;
}
GLuint DrawingInstance::getMyShader()
{
	return _myShaderID;
}
void DrawingInstance::setMyShader(GLuint _ShaderID)
{ 
	_myShaderID = _ShaderID;
}

void DrawingInstance::giveTexture(Texture& giveThis)
{
	_hasTexture = true;
	_myTexture = &giveThis;
}

Texture& DrawingInstance::getTexture()
{
	return *_myTexture;
}

DrawingInstance::DrawingInstance()
{
	_hasTexture = false;
	_hasMesh = false;
}