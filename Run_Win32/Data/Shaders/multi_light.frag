#version 410 core

//Textures
uniform sampler2D gTexDiffuse;
uniform sampler2D gTexNormal;
uniform sampler2D gTexSpecular;

//General for light
uniform vec4 gAmbientLight;
uniform vec3 gCameraPosition;

//Fog
uniform float gFogMinDistance;
uniform float gFogMaxDistance;
uniform vec4 gFogColor;

//Needed for any light
uniform vec3 gLightPosition[16];
uniform vec3 gLightDirection[16];
uniform vec4 gLightColor[16];
uniform float gMinLightDistance[16];
uniform float gMaxLightDistance[16];
uniform float gMinLightPower[16];
uniform float gMaxLightPower[16];

uniform float gSpecularPower;

//Needed for cone light
uniform int gInterpolateAttenuation[16];
uniform float gThetaInner[16];
uniform float gThetaOuter[16];
uniform float gLightInsidePower[16];
uniform float gLightOutsidePower[16];

uniform int gLightCount;

uniform int gWhatToRender;

//Passed params
in vec2 passUV0;
in vec3 passPosition;
in vec4 passColor;
in vec3 passTangent;
in vec3 passBitangent;

//Out params
out vec4 outColor;

vec3 m_finalColor = vec3(0.f, 0.f, 0.f);
vec3 m_normal = vec3(0.f, 0.f, 0.f);

bool isUsingNormal = false;

//---------------------------------------------------------------------------------------------------------------------------
//TOOLBOX FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
float RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd) {
	return (((inValue - inStart) / (inEnd - inStart)) * (outEnd - outStart)) + outStart;
}

vec3 GetNormal() {
	vec3 tangent = normalize(passTangent);
	vec3 bitangent = normalize(passBitangent);
	vec3 surfaceNormal = cross(tangent, bitangent);
	mat3 tbn = mat3(tangent, bitangent, surfaceNormal);
	tbn = transpose(tbn);

	vec3 normal = texture(gTexNormal, passUV0).xyz;
	normal = normal * vec3(2.f, 2.f, 1.f) - vec3(1.f, 1.f, 0.f);
	return normal * tbn;
}

//---------------------------------------------------------------------------------------------------------------------------
//CALCULATE LIGHT FACTOR
//---------------------------------------------------------------------------------------------------------------------------
vec4 CalculateLightFromAll() {
	vec3 ambientLight =	gAmbientLight.rgb * gAmbientLight.a;
	vec3 surfaceLight = vec3(0.f, 0.f, 0.f);
	vec3 specColor = vec3(0.f, 0.f, 0.f);

	float attenuation;
	float attDist;
	float attAngle;
	float amount;

	for(unsigned int idx = 0; idx < gLightCount; idx++) {
		vec3 vec_to_light = gLightPosition[idx] - passPosition;
		float dist = length(vec_to_light);
		vec_to_light = normalize(vec_to_light);
		vec3 normal = GetNormal();

		//ATTENUATION
		attDist = smoothstep(gMinLightDistance[idx], gMaxLightDistance[idx], dist);
		attDist = mix(gMinLightPower[idx], gMaxLightPower[idx], attDist);

		vec3 ldNorm = normalize(gLightDirection[idx]);
		vec3 ld = mix(-vec_to_light, ldNorm, gInterpolateAttenuation[idx]);
		float ld_dot_ldNorm = clamp(dot(ld, ldNorm), 0.f, 1.f);

		attAngle = smoothstep(gThetaInner[idx], gThetaOuter[idx], ld_dot_ldNorm);
		attAngle = mix(gLightInsidePower[idx], gLightOutsidePower[idx], attAngle);

		attenuation = attDist * attAngle;

		amount = clamp(dot(vec_to_light, normal), 0.f, 1.f);
	
		surfaceLight += gLightColor[idx].xyz * attenuation * amount;

		//SPECULAR
		float specular_intensity = texture(gTexSpecular, passUV0).r;
		vec3 vec_to_eye = normalize(gCameraPosition - passPosition);
		vec3 half_vector = vec_to_light + vec_to_eye;
		half_vector = normalize(half_vector);
		float half_dot_normal = clamp(dot(half_vector, normal), 0.f, 1.f);
		float intensity = pow(half_dot_normal, gSpecularPower) * specular_intensity * attenuation;

		specColor += intensity * gLightColor[idx].xyz;
	}

	surfaceLight = clamp(surfaceLight, 0.f, 1.f);
	specColor = clamp(specColor, 0.f, 1.f);

	m_finalColor = vec3(amount);

	vec4 textureColor = texture(gTexDiffuse, passUV0);
	return textureColor * (vec4(ambientLight, 1.f) + vec4(surfaceLight, 1.f)) + vec4(specColor, 1.f);
}

//---------------------------------------------------------------------------------------------------------------------------
//FOG FACTOR
//---------------------------------------------------------------------------------------------------------------------------
float CalculateFogFactor() {
	vec3 vecToCamera = gCameraPosition - passPosition;
	float dist = length(vecToCamera);
	float fogFactor = (gFogMaxDistance - dist) / (gFogMaxDistance - gFogMinDistance);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	return fogFactor;
}

//---------------------------------------------------------------------------------------------------------------------------
//MAIN
//---------------------------------------------------------------------------------------------------------------------------
void main() {
	float fogFactor = CalculateFogFactor();

	vec4 finalColor = CalculateLightFromAll();
	
	outColor = finalColor;

	if(gWhatToRender == 1) { //Positional data
		outColor = passColor;
	}
	else if(gWhatToRender == 2) { //UV's
		outColor = vec4(passUV0.x, passUV0.y, 0.f, 1.f);
	}
	else if(gWhatToRender == 3) { //Normals
		outColor = vec4(m_normal.x, m_normal.y, m_normal.z, 1.f);
	}
	
}
