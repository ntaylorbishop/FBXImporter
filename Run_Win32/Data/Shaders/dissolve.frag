#version 410 core

//Textures
uniform sampler2D gTexDiffuse;
uniform sampler2D gTexNormal;
uniform sampler2D gTexSpecular;
uniform sampler2D gTexDissolve;
uniform sampler2D gTexBurnGradient;

//Lighting
uniform vec4 gAmbientLight;
uniform vec3 gLightPosition;
uniform float gLightIntensity;
uniform vec4 gLightColor;

//Specular light
uniform float gSpecularPower;
uniform vec3 gCameraPosition;

//Fog
uniform float gFogMinDistance;
uniform float gFogMaxDistance;
uniform vec4 gFogColor;

//Dissolve
uniform float gAge;

//Passed params
in vec2 passUV0;
in vec3 passPosition;
in vec3 passTangent;
in vec3 passBitangent;

//Out params
out vec4 outColor;

//---------------------------------------------------------------------------------------------------------------------------
//TOOLBOX FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
float RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd) {
	return (((inValue - inStart) / (inEnd - inStart)) * (outEnd - outStart)) + outStart;
}

//---------------------------------------------------------------------------------------------------------------------------
//CALCULATE LIGHT FACTOR
//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
//CALCULATE SPECULAR FACTOR
//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
//GET TBN
//---------------------------------------------------------------------------------------------------------------------------
mat3 GetTBN() {
	vec3 tangent = normalize(passTangent);
	vec3 bitangent = normalize(passBitangent);
	vec3 surfaceNormal = cross(tangent, bitangent);
	mat3 tbn = mat3(tangent, bitangent, surfaceNormal);
	tbn = transpose(tbn);
	return tbn;
}

float CalculateFogFactor() {
	vec3 vecToCamera = gCameraPosition - passPosition;
	float dist = length(vecToCamera);
	float fogFactor = (gFogMaxDistance - dist) / (gFogMaxDistance - gFogMinDistance);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	return fogFactor;
}

bool FragNeedsToBeDiscarded() {
	vec4 dissolveColor = texture(gTexDissolve, passUV0);

	if(dissolveColor.r  < gAge) {
		return true;
	}
	else {
		return false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//MAIN
//---------------------------------------------------------------------------------------------------------------------------
void main() {
	vec4 textureColor = texture(gTexDiffuse, passUV0);

	//Compute TBN
	vec3 normal = texture(gTexNormal, passUV0).xyz;
	normal = normal * vec3(2.f, 2.f, 1.f) - vec3(1.f, 1.f, 0.f);
	vec3 final_normal = normal * GetTBN();

	vec3 light_intensity = CalculateLightFactor(final_normal);
	vec3 spec_factor = CalculateSpecularFactor(final_normal);
	float fogFactor = CalculateFogFactor();

	vec4 finalColor = vec4(light_intensity, 1.0f) * textureColor + vec4(spec_factor, 1.f);
	finalColor = clamp(finalColor, vec4(0.f), vec4(1.f));

	vec4 burnFactor = vec4(0.f, 0.f, 0.f, 1.f);
	if(FragNeedsToBeDiscarded()) {
		discard;
	}
	else {
		float amount = 0.1f;
		vec3 test = texture(gTexDissolve, passUV0).rgb - gAge;

		if(test.r < amount && gAge > 0 && gAge < 1) {
			burnFactor = texture(gTexBurnGradient, vec2(test.r * ( 1 / amount), 0));
		}
	}


	outColor = mix(gFogColor, finalColor, fogFactor) + burnFactor;

	//outColor = texture(gTexDissolve, passUV0);

}
