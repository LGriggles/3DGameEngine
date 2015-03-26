#ifndef CAMERA_H
#define CAMERA_H

//C++
#include <vector>
using std::vector;

//OPENGL
#include <GL\glew.h>

//SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

//GLM
#include <gtx\transform.hpp>
#include <glm.hpp>

//3DGameEngine
#include "Actor.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"

/*! Handles the camera */
class Camera
{
private:
	bool _hasTarget;				//!< Does I have a target
	glm::mat4 _mProj;				//!< The projection matrix
	glm::mat4 _mView;				//!< The view matrix

	GLuint _baseShaderID;			//!< The ID of the shader				
	GLuint _viewMatrixID;			//!< View matrix ID
	GLuint _projectionMatrixID;		//!< View matrix and projection matrix IDs for Opengl

	glm::vec3* _targetPtr;			//!< Points to a target object
	glm::vec3 _position;			//!< Position of the camera
	glm::vec3 _target;				//!< Target of the camera
	glm::vec3 _right;				//!< Right vector
	glm::vec3 _up;					//!< Up vector
	glm::vec3 _forward;				//!< Forward vector
	glm::vec3 _rotation;			//!< Rotation of the camera

	float _pitch;					//!< Pitch of the camera
	float _yaw;						//!< Yaw of camera
	float _roll;					//!< Roll of the camera
public:
	void init();									//!< Initialize
	void update();									//!< Update
	void prepareForDraw();							//!< Prepare the camera for drawing
	void StrafeRight(float speed);					//!< Move the position of the camera right in respect to its rotation
	void StrafeLeft(float speed);					//!< Move the position of the camera left in respect to its rotation
	void GoForward(float speed);					//!< Translate the camera forward
	void GoBackward(float speed);					//!< Translate the camera backward
	void rotate(float x, float y);					//!< Rotate the camera in respect to itself
	void setPosition(const glm::vec3& position);	//!< Set the position of the camera in respect to its current position
	void setTarget(glm::vec3& _target)
	{
		_targetPtr = &_target;
		_hasTarget = true;
	}
	void setRotation(glm::vec3 r)
	{ _rotation = r; }
	glm::vec3 getRotation()
	{ return _rotation; };
	glm::vec3 getPosition()  						//!< get the position
	{ return _position; };
	glm::mat4 getProjectionMatrix()					//!< get projection matrix
	{ return _mProj; };
	glm::mat4 getViewMatrix()						//!< get view matrix
	{ return _mView; };		
private:
	void complete();	//!< Only called by camera, finalizes matrices and other aspects
};
#endif