#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Material/Shaders/ShaderProgram.hpp"
#include "Engine/Renderer/Renderer/RenderState.hpp"
#include "Engine/Renderer/Light3D.hpp"
#include "Engine/Renderer/Material/Shaders/Sampler2D.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"

class Material {
public:
	//STRUCTORS
	Material();
	Material(const String& vertShaderLoc, const String& fragShaderLoc, const std::vector<Uniform*> uniforms);
	~Material();

	//USING MATERIAL
	void UseMaterial(const VertexDefinition& vertexDef);
	void StopUsingMaterial();

	//UNIFORMS
	Uniform* GetUniform(const String& uniformName);
	void UpdateUniform(Uniform* newUniform);

public:
	std::vector<Uniform*> m_uniforms;
	
private:
	ShaderProgram m_shaderProgram;
};