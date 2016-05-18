#version 410 core

//Noise animation - Electric
//by nimitz (stormoid.com) (twitter: @stormoid)

uniform float     gAge;           // shader playback time (in seconds)

//Textures
uniform sampler2D gTexDiffuse;
uniform sampler2D gTexNormal;
uniform sampler2D gTexSpecular;

//Passed params
in vec4 passColor;
in vec2 passUV0;
in vec3 passPosition;
in vec3 passTangent;
in vec3 passBitangent;

//Out params
out vec4 outColor;

#define PI 3.1415926535

void main() {
	vec4 textureColor = texture(gTexDiffuse, passUV0);
	vec2 scale = passPosition.xy;
	float v = 0.0;
	vec2 c = textureColor.xy * scale - scale/90.0;
	v += 0.1 * sin((c.x + gAge));
	v += 0.1 * sin((c.y + gAge) / 2.0);
	v += 0.1 * sin((c.x + c.y + gAge) / 2.0);
	c += scale / 2.0 * vec2( 0.1 *sin(gAge / 3.0), 0.1 *cos(gAge / 2.0));
	v += sin(sqrt(c.x * c.x + c.y * c.y + 1.0) + gAge);
	v = v;
	vec3 col = vec3(1, sin(PI*v), cos(PI*v));
	outColor =  vec4(col*.5 + .1, 1);

}