#include "Game/MaterialManager.hpp"

MaterialManager* g_theMaterialManager = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
MaterialManager::MaterialManager() {
	InitializeMaterials();
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void MaterialManager::UpdateUniformOnMaterial(const String& materialName, Uniform* uniform) {
	ASSERT_OR_DIE(uniform != nullptr, "NULL UNIFORM PASSED IN IN UPDATEUNIFORMFORMATERIAL");

	std::map<string, Material*>::iterator matIterator = m_materials.find(materialName);

	Material* mat = matIterator->second;

	for (unsigned int i = 0; i < mat->m_uniforms.size(); i++) {
		Uniform* currUniform = mat->m_uniforms[i];

		if (currUniform->GetName() == uniform->GetName()) {
			mat->m_uniforms[i] = uniform;
		}
	}
}
void MaterialManager::UpdateUniformOnAllMaterials(Uniform* uniform) {
	std::map<string, Material*>::iterator matIterator;

	for (matIterator = m_materials.begin(); matIterator != m_materials.end(); ++matIterator) {
		Material* currMat = matIterator->second;

		for (unsigned int i = 0; i < currMat->m_uniforms.size(); i++) {
			Uniform* currUniform = currMat->m_uniforms[i];

			if (currUniform->GetName() == uniform->GetName()) {
				currMat->m_uniforms[i] = uniform;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//GETTERS SETTERS
//---------------------------------------------------------------------------------------------------------------------------
Material* MaterialManager::GetMaterial(const String& materialName) {
	std::map<string, Material*>::iterator matIterator = m_materials.find(materialName);

	if (matIterator == m_materials.end()) {
		return nullptr;
	}
	else {
		return matIterator->second;
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
void MaterialManager::InitializeMaterials() {
	CreateBrickMaterial();
	CreateFBOMaterial_1();
	CreateFBOMaterial_2();
	CreateFBOMaterial_3();
	CreateFBOMaterial_4();
	CreateFBOMaterial_5();
	CreateFBOMaterial_6();

}
void MaterialManager::CreateBrickMaterial() {
	std::vector<Uniform*> brickUniforms;

	//Sampler
	Sampler2D brickSampler;
	brickSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture("Data/Textures/black.png"));
	brickSampler.AddTexture("gTexNormal", Texture::CreateOrGetTexture("Data/Textures/Black_Normal.png"));
	Uniform* brickSamplerUniform = new Uniform_SAMPLER2D(brickSampler);
	brickUniforms.push_back(brickSamplerUniform);

	//General uniforms
	brickUniforms.push_back(new Uniform_RGBA("gAmbientLight", MATERIAL_AMBIENT_LIGHT));
	brickUniforms.push_back(new Uniform_FLOAT("gSpecularPower", MATERIAL_SPEC_POWER));
	brickUniforms.push_back(new Uniform_FLOAT("gFogMinDistance", MATERIAL_MIN_FOG_DISTANCE));
	brickUniforms.push_back(new Uniform_FLOAT("gFogMaxDistance", MATERIAL_MAX_FOG_DISTANCE));
	brickUniforms.push_back(new Uniform_RGBA("gFogColor", MATERIAL_FOG_COLOR));

	//Changing uniforms
	brickUniforms.push_back(new Uniform_VECTOR3("gCameraPosition", Vector3(0.f, 0.f, 0.f)));
	brickUniforms.push_back(new Uniform_INT("gWhatToRender", 0));

	//Uniforms for lights
	std::vector<Vector3> lightPositions;
	std::vector<Vector3> lightDirections;
	std::vector<RGBA>    lightColors;
	std::vector<float>   minLightDists;
	std::vector<float>   maxLightDists;
	std::vector<float>   minPowers;
	std::vector<float>   maxPowers;
	std::vector<float>   dirInterps;
	std::vector<float>   innerThetas;
	std::vector<float>   outerThetas;
	std::vector<float>   thetaInnerPowers;
	std::vector<float>   thetaOuterPowers;

	for (unsigned int i = 0; i < 16; i++) {
		lightPositions.push_back(Vector3(0.f, 0.f, 0.f));
		lightDirections.push_back(Vector3(0.f, 0.f, 0.f));
		lightColors.push_back(RGBA(0.f, 0.f, 0.f, 0.f));
		minLightDists.push_back(0.f);
		maxLightDists.push_back(0.f);
		minPowers.push_back(0.f);
		maxPowers.push_back(0.f);
		dirInterps.push_back(0);
		innerThetas.push_back(0.f);
		outerThetas.push_back(0.f);
		thetaInnerPowers.push_back(0.f);
		thetaOuterPowers.push_back(0.f);
	}

	brickUniforms.push_back(new Uniform_INT("gLightCount", 1));
	brickUniforms.push_back(new Uniform_VECTOR3("gLightPosition", lightPositions));
	brickUniforms.push_back(new Uniform_VECTOR3("gLightDirection", lightDirections));
	brickUniforms.push_back(new Uniform_RGBA("gLightColor", lightColors));
	brickUniforms.push_back(new Uniform_FLOAT("gMinLightDistance", minLightDists));
	brickUniforms.push_back(new Uniform_FLOAT("gMaxLightDistance", maxLightDists));
	brickUniforms.push_back(new Uniform_FLOAT("gMinLightPower", minPowers));
	brickUniforms.push_back(new Uniform_FLOAT("gMaxLightPower", maxPowers));
	brickUniforms.push_back(new Uniform_FLOAT("gInterpolateAttenuation", dirInterps));
	brickUniforms.push_back(new Uniform_FLOAT("gThetaInner", innerThetas));
	brickUniforms.push_back(new Uniform_FLOAT("gThetaOuter", outerThetas));
	brickUniforms.push_back(new Uniform_FLOAT("gLightInsidePower", thetaInnerPowers));
	brickUniforms.push_back(new Uniform_FLOAT("gLightOutsidePower", thetaOuterPowers));
	
	brickUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	brickUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	brickUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	//BONE MATRICES
	std::vector<Matrix4> boneMatrices;
	for (unsigned int i = 0; i < 200; i++) {
		boneMatrices.push_back(Matrix4::IDENTITY);
	}
	brickUniforms.push_back(new Uniform_MAT4("gBoneMatrices", boneMatrices));

	Material* brick = new Material("Data/Shaders/multi_light.vert", "Data/Shaders/multi_light.frag", brickUniforms);
	m_materials.insert(std::pair<string, Material*>("Brick", brick));
}
void MaterialManager::CreateFBOMaterial_1() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_D24S8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));
	
	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process1.vert", "Data/Shaders/post_process1.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo1", fbo));
}
void MaterialManager::CreateFBOMaterial_2() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_RGBA8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process2.vert", "Data/Shaders/post_process2.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo2", fbo));
}
void MaterialManager::CreateFBOMaterial_3() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_RGBA8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process3.vert", "Data/Shaders/post_process3.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo3", fbo));
}
void MaterialManager::CreateFBOMaterial_4() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_RGBA8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process4.vert", "Data/Shaders/post_process4.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo4", fbo));
}
void MaterialManager::CreateFBOMaterial_5() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_RGBA8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process5.vert", "Data/Shaders/post_process5.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo5", fbo));
}
void MaterialManager::CreateFBOMaterial_6() {
	std::vector<Uniform*> fboUniforms;

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture(0, 1600, 900, eTextureFormat_RGBA8));
	fboSampler.AddTexture("gTexDepth", Texture::CreateOrGetTexture(1, 1600, 900, eTextureFormat_RGBA8));
	Uniform* fboSamplerUniform = new Uniform_SAMPLER2D(fboSampler);
	fboUniforms.push_back(fboSamplerUniform);

	//General uniforms
	fboUniforms.push_back(new Uniform_MAT4("gModel", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gView", Matrix4::IDENTITY));
	fboUniforms.push_back(new Uniform_MAT4("gProj", Matrix4::IDENTITY));

	fboUniforms.push_back(new Uniform_FLOAT("gAge", 0.f));

	Material* fbo = new Material("Data/Shaders/post_process6.vert", "Data/Shaders/post_process6.frag", fboUniforms);
	m_materials.insert(std::pair<string, Material*>("fbo6", fbo));
}