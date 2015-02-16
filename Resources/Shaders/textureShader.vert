#version 430

layout (location=0) in vec3 vertPosition;
layout (location=1) in vec2 textureCoord;
layout (location=2) in vec3 vertNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 oTextureCoord;			//UV coordinate
out vec3 oLightPosition;		//Out light position
out vec3 oVertexPosition;		//Out vertex position
out vec3 oNormal;				//Light normal

uniform vec3 lightPosition;		//Light position

void main()
{
	mat4 mMvM = viewMatrix * modelMatrix;	//Model matrix view matrix
	mat3 normalMatrix = mat3(vec3(mMvM[0]),vec3(mMvM[1]),vec3(mMvM[2]));
	oVertexPosition = vec3(viewMatrix * modelMatrix * vec4(vertPosition,1.0)); 
	oLightPosition = vec3(viewMatrix * modelMatrix * vec4(lightPosition,1.0));  
	oNormal = normalize(normalMatrix * vertNormal);
	oTextureCoord = textureCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPosition,1);	//Vertex position calculation
}
