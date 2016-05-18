#version 410 core

uniform sampler2D gTexDiffuse;
uniform sampler2D gTexNormal;
uniform sampler2D gTexSpecular;
uniform sampler2D gTexEmissive;

uniform vec4 gAmbientLight;
uniform vec3 gLightPosition;
uniform float gLightIntensity;
uniform vec4 gLightColor;

uniform int hasEmissive;
uniform float gAge;

//Specular light
uniform float gSpecularPower;
uniform vec3 gCameraPosition;

uniform float gFogMinDistance;
uniform float gFogMaxDistance;
uniform vec4 gFogColor;


in vec2 passUV0;
in vec3 passPosition;
in vec3 passTangent;
in vec3 passBitangent;

out vec4 outColor;

vec3 CalculateEmissiveStrength() {
	if(hasEmissive == 1) {
		return texture(gTexEmissive, passUV0).rgb * texture(gTexEmissive, passUV0).a * gAge;
	}
	else {
		return vec3(0.f, 0.f, 0.f);
	}
}

vec3 CalculateLightFactor(vec3 normal) {
	//Get a vector from the light 
	vec3 light_intensity = gAmbientLight.rgb * gAmbientLight.a;
	vec3 vec_to_light = gLightPosition - passPosition;

	float inv_len = dot(vec_to_light, vec_to_light);
	inv_len = inversesqrt(inv_len);

	vec_to_light = vec_to_light * inv_len;
	float power = gLightIntensity * (inv_len * inv_len); 

	vec_to_light = normalize(vec_to_light);

	float n_dot_l = clamp(dot(normal, vec_to_light), 0.f, 1.f);
	light_intensity += vec3(n_dot_l) * gLightColor.rgb * power;
	light_intensity = clamp(light_intensity, vec3(0.f), vec3(1.f));

	return light_intensity;
}

vec3 CalculateSpecularFactor(vec3 normal) {
	float specular_intensity = texture(gTexSpecular, passUV0).r;

	vec3 vec_to_light = gLightPosition - passPosition;

	float power = dot(vec_to_light, vec_to_light);
	power = gLightIntensity / power;
	vec_to_light *= inversesqrt(power);

	vec3 vec_to_eye = normalize(gCameraPosition - passPosition);
	vec3 half_vector = vec_to_light + vec_to_eye;
	half_vector = normalize(half_vector);

	float half_dot_normal = clamp(dot(half_vector, normal), 0.f, 1.f);
	float intensity = pow(half_dot_normal, gSpecularPower) * specular_intensity;


	vec4 color = intensity * gLightColor * power;
	return color.rgb;
}

float RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd) {
	return (((inValue - inStart) / (inEnd - inStart)) * (outEnd - outStart)) + outStart;
}


void main() {
	vec4 textureColor = texture(gTexDiffuse, passUV0);
	vec3 normal = texture(gTexNormal, passUV0).xyz;

	vec3 tangent = normalize(passTangent);
	vec3 bitangent = normalize(passBitangent);
	vec3 surfaceNormal = cross(tangent, bitangent);
	mat3 tbn = mat3(tangent, bitangent, surfaceNormal);
	tbn = transpose(tbn);


	normal = normal * vec3(2.f, 2.f, 1.f) - vec3(1.f, 1.f, 0.f); //Maps to a range (-1 1, -1 1, 0 1)
	vec3 final_normal = normal * tbn;

	//vec3 final_normal = vec3(normal.x, -normal.z, normal.y);
	//final_normal = normalize(final_normal);

	vec3 light_intensity = CalculateLightFactor(final_normal);
	vec3 spec_factor = CalculateSpecularFactor(final_normal);
	vec3 emissive_factor = CalculateEmissiveStrength();

	//Calculate fog factor
	vec3 vecToCamera = gCameraPosition - passPosition;
	float dist = length(vecToCamera);
	// 20 - fog starts; 80 - fog ends
	float fogFactor = (gFogMaxDistance - dist)/(gFogMaxDistance - gFogMinDistance);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );

	vec4 finalColor = vec4(light_intensity + emissive_factor, 1.0f) * textureColor + vec4(spec_factor, 1.f);
	finalColor = clamp(finalColor, vec4(0.f), vec4(1.f));

	outColor = mix(gFogColor, finalColor, fogFactor);

	//outColor = gAmbientLight;
}
