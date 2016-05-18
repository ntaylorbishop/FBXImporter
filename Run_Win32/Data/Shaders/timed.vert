#version 410 core

uniform mat4 gModel;
uniform mat4 gView;
uniform mat4 gProj;
uniform float gAge;

in vec3 inPosition;
in vec4 inColor;
in vec2 inUV0;

out vec4 passColor;
out vec2 passUV0;

void main ( void ) {
	passColor = vec4(cos(gAge), sin(gAge), sin(gAge), 1.0f);
	passUV0 = inUV0;

	vec3 newPos = vec3(inPosition.x + cos(gAge), inPosition.y + sin(gAge), inPosition.z);

	vec4 pos = vec4(newPos, 1.0f);
	pos = pos * gModel * gView * gProj; //row major

	gl_Position = pos;
}