#version 410 core

#define PI 3.141592653589
#define PI2 6.28318530718

uniform sampler2D gTexDiffuse;
uniform sampler2D gTexDepth;

uniform float gAge;

in vec2 passUV0;

out vec4 outColor;

vec2 iResolution = vec2(1600.f, 900.f);

vec2 hash( vec2 p ) {
	p = vec2( dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3)));
	return fract(sin(p)*43758.5453);
}
float rand(float n) {
	return fract(sin(n) * 43758.5453123);
}
float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

vec4 mapStar(vec2 position, float lightSpeed, float angleOffset) {
	
	vec4 color = vec4(vec3(0.), 1.);
	
	float angle = atan(position.y, position.x) + angleOffset;
	
	float angleNumber = 20.;
	
	float random = rand(floor(angle * angleNumber) * 100.);
	
	float distance = random;
	distance += gAge * 2.;
	distance = fract(distance);
	
	float fragDistance = length(position);
	
	float size = smoothstep(-.1, 2., lightSpeed);
	
	float bounded = step(distance, fragDistance) * step(fragDistance, distance + size);
	bounded += step(fragDistance, fract(distance + size)) * step(fract(distance + size), distance);
	
	color.rgb = mix(vec3(0.), vec3(1.), bounded);
	
	color.r *= 1.;
	color.g *= .7 + random * .3;
	color.b *= 4.;
	
	// hard edges
	float angleCenter = abs(fract(angle * angleNumber) * 2. - 1.);
	color.a = step(angleCenter, smoothstep(-.2, 1., lightSpeed));
	
	// smooth gradient
	color.a *= 1. - angleCenter;
	
	color.a *= smoothstep(0., 1., fragDistance);
	color.a *= cos(random * gAge) * .5 + .5;
	
	return color;
}

void main( void ) {
	
	float lightSpeed = cos(gAge) * .5 + .5;
	
	lightSpeed = 100.f / iResolution.x;
	
	//lightSpeed = 1.;
	
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	
	vec2 position = uv * 2. - 1.;
	position.y *= iResolution.y / iResolution.x;
	
	vec4 color = vec4(0.05);
	
	for(float i = 0.; i < 2.; i++) {
		vec4 starColor = mapStar(position, lightSpeed, i * 20.);
		color.rgb += starColor.rgb * starColor.a;
	}
		
	outColor = texture(gTexDiffuse, passUV0) * color;
}