#version 410 core


in vec3 inPosition;
in vec4 inColor;

out vec4 passColor;

void main( void ) {
	gl_Position = vec4( inPosition, 1.0f );

	passColor = inColor;
}