#version 410

uniform mat4 gModel;
uniform mat4 gView;
uniform mat4 gProj;

in vec3 inPosition;
in vec2 inUV0;

out vec2 passUV0;

void main( void ) {
	passUV0 = vec2(inUV0.x, 1.0 - inUV0.y);

	vec4 pos = vec4(inPosition, 1.0f);
	pos = pos * gModel * gView * gProj;

	gl_Position = vec4( pos );
}
