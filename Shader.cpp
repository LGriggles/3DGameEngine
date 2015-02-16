//3DGameEngine
#include "stdafx.h"
#include "Shader.hpp"

//SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

void Shader::loadVariable(string variable)
{
	_shaderVariableLinks[variable] = glGetAttribLocation(_shaderProgramID,variable.c_str());
	std::cout << "hi" << std::endl;
}

GLuint Shader::getVariable(string variable)
{
	return _shaderVariableLinks[variable];
}

GLuint Shader::getUniformLocation(string uniform)
{
	return glGetAttribLocation(_shaderProgramID,uniform.c_str());
}

//Stores a uniform GLuint to a specified index
void Shader::storeUniform(int setUniformIndex, string uniformName)
{
	_uniforms[setUniformIndex] = glGetUniformLocation(_shaderProgramID,uniformName.c_str());
}

//Returns a stored uniform GLuint
GLuint Shader::getStoredUniform(int uniformIndex)
{
	return _uniforms[uniformIndex];
}

void Shader::createShader(string _vertShaderFile, string _fragShaderFile)
{
	//Compile vertex
	GLuint vertexShader;
	compileShaderFile(_vertShaderFile, vertexShader, GL_VERTEX_SHADER);
	//Compile fragment
	GLuint fragmentShader;
	compileShaderFile(_fragShaderFile, fragmentShader, GL_FRAGMENT_SHADER);

	_shaderProgramID = glCreateProgram();
	if(_shaderProgramID == 0) 
	{
		fprintf(stderr, "Could not create the program object");
		exit(1);
	}

	glAttachShader(_shaderProgramID, vertexShader);
	glAttachShader(_shaderProgramID, fragmentShader);

	glLinkProgram(_shaderProgramID);

	//ERROR HANDLING for program compilation
	GLint status;
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &status );
	if (status == FALSE) //Fail
	{
		fprintf(stderr, "");
		GLint logLen;
		glGetProgramiv( _shaderProgramID, GL_INFO_LOG_LENGTH, &logLen );
		if (logLen > 0) 
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(_shaderProgramID, logLen, &written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log); //Error log
		}
	}
	else 
	{
		glUseProgram(_shaderProgramID);
	}
}

void Shader::compileShaderFile(string shaderFilePath, GLuint& shaderProgram, GLenum shaderType)
{
	ifstream shaderFile(shaderFilePath);
	if (!shaderFile)
	{
		fprintf(stderr, ("ERROR: cannot open file"));
		exit(1);
	}
	std::stringstream sourceCode;
	sourceCode << shaderFile.rdbuf();
	shaderFile.close();
	string codeStr(sourceCode.str());
	shaderProgram = glCreateShader(shaderType);
	if (shaderFile == 0)
	{
		fprintf(stderr, "ERROR: Cannot create shader");
		exit(EXIT_FAILURE);
	}
	const GLchar* codeArray[] = 
	{
		codeStr.c_str()
	};
	glShaderSource(shaderProgram, 1, codeArray, NULL);
	glCompileShader(shaderProgram);
	GLint result;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &result);
	if(result == FALSE) 
	{
		fprintf(stderr, "ERROR: compilation failed!" );

		GLint logLength;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0) {
			char * log = (char *)malloc(logLength);

			GLsizei written;
			glGetShaderInfoLog(shaderProgram, logLength, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}
}