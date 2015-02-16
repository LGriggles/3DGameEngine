#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "glm.hpp"

#define PI			3.14159265358979323846

class Quaternion  
{
	public:
		glm::mat4x4 _rotationMatrix;

		Quaternion();
		~Quaternion();
		
		void CreateMatrix();
		void CreateFromAxisAngle(const float &in_x,
								 const float &in_y,
								 const float &in_z,
								 const float &in_degrees);

		Quaternion operator *(const Quaternion &q);


	private:
		
		float x,
			  y,
			  z,
			  w;
};


#endif