#version 430

in vec2 oTextureCoord;
in vec3 oLightPosition;
in vec3 oVertexPosition;
in vec3 oNormal;

out vec4 fragColour;

uniform sampler2D tex; //The texture

uniform vec3 tint = vec3(0,0,0);

void main() 
{
	vec3 Ks = vec3(1.0f, 1.0f, 1.0f);				//Specular reflection constant
	vec3 Kd = vec3(1.0f, 1.0f, 1.0f);;				//Diffuse reflectivity
	vec3 Ka = vec3(0.4f, 0.4f, 0.4f);;				//Ambient light reflectivity

	vec3 LightAmbient	= vec3(0.5f, 0.5f, 0.5f);	//Ambient light intensity
	vec3 LightSource	= vec3(1.0f, 1.0f, 1.0f);	//Light source
	vec3 LightDiffuse	= vec3(1.0f, 1.0f, 1.0f);	//Diffuse light intensity
	
	//Calculate the light vector
	vec3 L = normalize(oLightPosition - oVertexPosition);  
	vec3 R = 2 * oNormal * max((dot(oNormal,L)), 0.0) - L;
	vec3 V = normalize(-oVertexPosition);
	
	//Calculate ambient
	vec4 ambientIntensity = vec4(Ka,1.0) * vec4(LightAmbient, 0.1);

	//Calculate diffuse
	vec4 diffuseIntensity = vec4(Kd,1.0) * vec4(LightDiffuse,1.0) * max(dot(oNormal,L), 0.0);
	diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

	//Calculate specular
	vec4 sourceIntensity = vec4(Ks,1.0) * vec4(LightSource,1.0) * pow(max(dot(R,V),0.0), 32);

    //Apply phong
	vec4 phongColouring = ambientIntensity + diffuseIntensity + sourceIntensity + vec4(tint,1.0);

	//Apply texture
	vec4 textureColour = texture(tex,oTextureCoord);

	//Mix
	phongColouring[3] = 1;
	fragColour = textureColour * phongColouring;
}
