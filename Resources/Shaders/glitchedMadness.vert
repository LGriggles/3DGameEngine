#version 430


layout (location=0) in vec4 vertPosition;
layout (location=1) in vec3 vertColour;
 
uniform mat4 projViewModelMatrix;

out vec3 colour;

void main()
{
	colour = vertColour;
	gl_Position = projViewModelMatrix * vertPosition;
}
