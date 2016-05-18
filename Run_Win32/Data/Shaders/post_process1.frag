#version 410 core

uniform sampler2D gTexDiffuse;
uniform sampler2D gTexDepth;

uniform float gAge;

in vec2 passUV0;

out vec4 outColor;

void main ( void ) {
	vec4 diffuse = texture(gTexDiffuse, passUV0);
	float depth = texture(gTexDepth, passUV0).r;

	outColor = diffuse;

	//outColor = diffuse;
	//outColor = vec4(vec3(depth), 1.f);
}

/*
void main ( void ) {
	vec4 diffuse = texture(gTexDiffuse, passUV0);
	
	diffuse = diffuse * 3;
	diffuse = floor(diffuse);
	diffuse = diffuse / 3;

	float depth = texture(gTexDepth, passUV0).r;

	float depthHere = texture( gTexDepth, passUV0).r;
	float depthRight = texture( gTexDepth, passUV0 + vec2(.01f, 0.0f) ).r;
	float depthLeft = texture( gTexDepth, passUV0 - vec2(.01f, 0.0f) ).r;

	depthLeft = depthLeft * depthLeft;
	depthRight = depthRight * depthRight;

	float diff = abs(depthRight - depthLeft);
	if(diff > 0.03f) {
		outColor = vec4(0.5f, 0.5f, 0.5f, 1);
	} else {
		outColor = vec4(1);
	}

	outColor = outColor * diffuse;

	//outColor = vec4(vec3(depth), 1.f);
}
*/

/*
void main( void ) {
	vec4 diffuse = texture(gTexDiffuse, passUV0);

	vec4 to_gray = vec4(.2126, .7152, .0722, 0.0);
	float gray = dot(diffuse, to_gray);

	vec3 r = vec3(0.9, 0.2, 0.19);
	vec3 p = vec3(0.0, .20, .33);
	vec3 l = vec3(0.95, 0.8, 0.7);
	vec3 b = vec3(0.4, 0.7, 0.8);

	vec3 color;
	if (gray < .1) {
		color = p;
	}
	else if (gray < 0.4) {
		color = r;
	}
	else if(gray < 0.7) {
		color = b;
	}
	else {
		color = l;
	}

	outColor = vec4(color, 1.0);
}
*/
