#version 410 core

uniform sampler2D gTexDiffuse;
uniform sampler2D gTexDepth;

uniform float gAge;

in vec2 passUV0;

out vec4 outColor;

void main ( void ) {
	vec2 uvDistorted = passUV0 + (0.01f * cos(gAge), 0.01f * sin(gAge));
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
	if(diff > 0.003f) {
		outColor = vec4(0.5f, 0.5f, 0.5f, 1.f);
	} else {
		outColor = vec4(1);
	}

	outColor = outColor * texture(gTexDiffuse, uvDistorted);
	outColor = clamp(outColor, vec4(0), vec4(1));
	outColor = outColor * diffuse;
}