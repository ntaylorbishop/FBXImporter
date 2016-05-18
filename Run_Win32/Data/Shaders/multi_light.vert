#version 410 core

uniform mat4 gModel;
uniform mat4 gView;
uniform mat4 gProj;
uniform mat4 gBoneMatrices[200];
uniform float gAge;

in vec3 inPosition;
in vec4 inColor;
in vec2 inUV0;
in vec3 inNormal;
in vec3 inTangent;
in vec3 inBitangent;
in vec4 inBoneWeights;
in ivec4 inBoneInds;

out vec4 passColor;
out vec2 passUV0;
out vec3 passPosition;
out vec3 passTangent;
out vec3 passBitangent;

void main ( void ) {
	passColor = inColor;
	passUV0 = inUV0;

	vec4 pos = vec4(inPosition, 1.0f);

	mat4 bone0 = gBoneMatrices[inBoneInds.x];
	mat4 bone1 = gBoneMatrices[inBoneInds.y];
	mat4 bone2 = gBoneMatrices[inBoneInds.z];
	mat4 bone3 = gBoneMatrices[inBoneInds.w];

	mat4 boneTransform = inBoneWeights.x * bone0
					   + inBoneWeights.y * bone1
					   + inBoneWeights.z * bone2
					   + inBoneWeights.w * bone3;

	mat4 modelToWorld = boneTransform * gModel;
	
	passPosition = (vec4(inPosition, 1.f) * modelToWorld).xyz;
	passTangent = (vec4(inTangent, 0.f) * modelToWorld).xyz;
	passBitangent = (vec4(inBitangent, 0.f) * modelToWorld).xyz;
	
	passColor = vec4(vec3(inBoneWeights.w), 1.f);
	//passColor = inColor;
	//pos = pos * modelToWorld * gView * gProj;

	gl_Position = vec4(inPosition, 1.0f) * modelToWorld * gView * gProj;
}