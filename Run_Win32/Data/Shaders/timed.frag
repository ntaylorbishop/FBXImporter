#version 410 core

uniform vec4 gColor;
uniform sampler2D gDiffuseTex;
uniform float gAge;

in vec4 passColor;
in vec2 passUV0;
in vec3 passBroken;

out vec4 outColor;

void main ( void ) {

	vec4 diffuse = texture(gDiffuseTex, passUV0);
	outColor = passColor * gColor * diffuse;
}