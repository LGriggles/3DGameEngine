#version 430

in vec3 colour;
out vec4 fragColour;

void main()
{
	float lerpValue = gl_FragCoord.y / 500.0f;
    
    fragColour = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f),
        vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}
