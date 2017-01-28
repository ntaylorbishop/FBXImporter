#pragma once

#include "Engine/Renderer/Material/Shaders/Uniform.hpp"
#include "Engine/Renderer/Material/Shaders/Shader.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"

class ShaderProgram {
public:
	//STRUCTORS
	ShaderProgram();
	ShaderProgram(const Shader& vShader, const Shader& fShader);

	void UseProgram() const;
	
// 	void BindProperty(const std::string& name, int32_t count, int32_t type, bool normalize, int stride, int offset) const;
// 
// 	void SetMatrix4(const std::string& nameInShader, const  Matrix4& mat) const;
// 	void SetInt(const std::string& nameInShader, int val) const;
// 	void SetColor(const std::string& nameInShader, const RGBA& color) const;
// 	void SetFloat(const std::string& nameInShader, float val) const;
// 	void SetVector3(const std::string& nameInShader, const Vector3& vec3) const;
// 
// 	void SetIntArray(const std::string& nameInShader, std::vector<int>& vals) const;
// 	void SetColorArray(const std::string& nameInShader, std::vector<RGBA>& vals) const;
// 	void SetFloatArray(const std::string& nameInShader, std::vector<float>& vals) const;
// 	void SetVector3Array(const std::string& nameInShader, std::vector<Vector3>& vals) const;
// 
// 	void SetTextureBindPoint(const std::string& nameInShader, unsigned int bindPoint) const;

	void BindAttributes(const VertexDefinition& vertexDef) const;
	void BindUniforms(const std::vector<Uniform*> uniforms) const;

private:
	//Private member functions
	void GetAllActiveUniformsInShaders();

private:
	int m_programID;
	Shader m_vertexShader;
	Shader m_fragmentShader;

	std::map<string, Uniform*> m_uniforms;
};