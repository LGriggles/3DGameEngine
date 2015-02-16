#version 430

layout (location=0) in vec4 vertPosition;
layout (location=1) in vec2 textureCoord;
layout (location=2) in vec3 vertNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 oVertColour;

void main()
{
	oVertColour = vertNormal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertPosition;	//Vertex position calculation
}
