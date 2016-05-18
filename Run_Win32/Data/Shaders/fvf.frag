#version 410 core

uniform vec4 gColor;
uniform sampler2D gDiffuseTex;

in vec4 passColor;
in vec2 passUV0;
in vec3 passBroken;

out vec4 outColor;
//out vec3 broken;

void main ( void ) {

	vec4 diffuse = texture(gDiffuseTex, passUV0);
	outColor = passColor * gColor * diffuse;
	//broken = passBroken;


}