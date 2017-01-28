#pragma once

#include <string>
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/General/Utils/FileUtils.hpp"



class Shader {
public:
	//STRUCTORS
	Shader();
	Shader(std::string fileName, eShaderType type);
	~Shader();

	//LOADING
	void Load();
	void Delete();

	//GETTERS SETTERS
	std::string GetFileName();
	eShaderType GetShaderType();
	int GetShaderID();

private:
	void LogCompileError();
	int GetShaderTypeEnum();

private:
	int m_shaderID;
	std::string m_fileName;
	eShaderType m_type;
};