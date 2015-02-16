#include "Quaternion.hpp"

Quaternion::Quaternion()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{

}

Quaternion::~Quaternion()
{

}

void Quaternion::CreateFromAxisAngle(const float &in_x, const float &in_y, const float &in_z, const float &in_degrees)
{
	
	float angle = float((in_degrees / 180.0f) * PI);
	float result = float(sin(angle/2.0f));
	w = float(cos(angle/2.0f));

	// Calculate the x, y and z of the quaternion
	x = float(in_x * result);
	y = float(in_y * result);
	z = float(in_z * result);
}

void Quaternion::CreateMatrix()
{

	s
		// First row
	    pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );  
	    pMatrix[ 1] = 2.0f * ( x * y - w * z );  
	    pMatrix[ 2] = 2.0f * ( x * z + w * y );  
	    pMatrix[ 3] = 0.0f;  
	
	    // Second row
	    pMatrix[ 4] = 2.0f * ( x * y + w * z );  
	    pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );  
	    pMatrix[ 6] = 2.0f * ( y * z - w * x );  
	    pMatrix[ 7] = 0.0f;  
	
	    // Third row
	    pMatrix[ 8] = 2.0f * ( x * z - w * y );  
	    pMatrix[ 9] = 2.0f * ( y * z + w * x );  
	    pMatrix[10] = 1.0f - 2.0f * ( x * x + y * y );  
	    pMatrix[11] = 0.0f;  
	
	    // Fourth row
	    pMatrix[12] = 0;  
	    pMatrix[13] = 0;  
	    pMatrix[14] = 0;  
	    pMatrix[15] = 1.0f;
}

Quaternion Quaternion::operator *(const Quaternion &q)
{
	Quaternion r;

	r.w = w*q.w - x*q.x - y*q.y - z*q.z;
	r.x = w*q.x + x*q.w + y*q.z - z*q.y;
	r.y = w*q.y + y*q.w + z*q.x - x*q.z;
	r.z = w*q.z + z*q.w + x*q.y - y*q.x;
	
	return r;
}