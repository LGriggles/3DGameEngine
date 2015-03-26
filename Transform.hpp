#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

//Opengl
#include <GL\glew.h>
//GLM
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\quaternion.hpp>
#include <gtx\transform.hpp>

/*! Handles position manipulation, is a component*/
class Transform
{
public:
	static glm::vec3 vectorToward(glm::vec3 point, glm::vec3 fromPoint)
    {
		glm::vec3 _currentResultantVector(0,0,0);
		_currentResultantVector.x =  point.x - fromPoint.x;
		_currentResultantVector.z =  point.z - fromPoint.z;

		float mag = (float)std::sqrt(std::pow(_currentResultantVector.x,2) + std::pow(_currentResultantVector.z,2));

         _currentResultantVector.x = _currentResultantVector.x/mag;
        _currentResultantVector.z = _currentResultantVector.z/mag;

        return _currentResultantVector;
    }

	static glm::vec3 lerp( const glm::vec3& A, const glm::vec3& B, float t ){
		return A*t + B*(1.f-t);
	}

	Transform();
	~Transform();
	void lookAt(glm::vec3 position);
	void translate(glm::vec3 position);		//!< Move the position in repsect to the current position
	void rotate(glm::vec3 rotation);		//!< Rotate the transform in respect to the current rotation	
	void rotateToward(glm::vec3 position);	//!< Rotate toward a specific point
	void setPosition(glm::vec3 position);	//!< Sets the absolute position of the transform in respect to the world origin
	void setScale(glm::vec3 scale);			//!< Scales the transform in respect to 0,0,0
	void translateForward(float amount);
	bool doAlookAt;
	glm::vec3 _target;
	glm::vec3 _forward;						//!< Forward vector specifies forward from the matrix
	glm::vec3 _scale;						//!< Scale vector specifices the current scale
	glm::vec3 _position;					//!< Position vector specifies the current position
	glm::vec3 _rotation;					//!< Rotation vector specifies the current rotation
	glm::vec3 _up;							//!< Up vector specifies up
	glm::vec3 _right;						//!< Right vector specifies right in respect to the matrix
	glm::mat4 getTransMatrix();				//!< Get the matrix, called for drawing
private:
	glm::mat4 _transformationMatrix;		//!< The transform matrix
};

#endif // !TRANSFORM_HPP
