#ifndef SHADER_HPP
#define SHADER_HPP

//C++
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
using std::ifstream;
using std::string;
using std::map;
//GLM
#include <GL\glew.h>
#include <glm.hpp>

/*! Handles shader creation */
class Shader
{
private:
	GLuint				_uniforms[50];			//!< Stored uniforms, used for caching locations of uniforms in the shaders
	map<string,GLuint>	_shaderVariableLinks;	//!< Stored variable links, used for caching variables in shaders to their respective names
	GLuint				_shaderProgramID;		//!< The shader program ID
public:
	void createShader(string vertShaderFile, string fragShaderFile);	//!< Create the shader
	void loadVariable(string variable);									//!< load a variable from the shader
	void storeUniform(int setUniformIndex, string uniformName);			//!< Cache the uniform to the specified index
	void compileShaderFile(string shaderFilePath,					
		GLuint& shaderProgram,
		GLenum shaderType);												//!< Compile the shader file
	GLuint getVariable(string variable);								//!< Get the handle of the specified variable
	GLuint getUniformLocation(string uniform);							//!< Cache the uniform shader location for the CPU
	GLuint getStoredUniform(int uniformIndex);							//!< Return the OpenGL uniform handle using the memory index
	GLuint getProgramID() { return _shaderProgramID; };					//!< Return the program ID
};
#endif