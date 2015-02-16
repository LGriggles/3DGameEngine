#version 430

in vec3 oVertColour;

uniform sampler2D tex; //The texture

out vec4 fragColour;

void main() {
	fragColour = vec4(oVertColour,1);
}
