#pragma once

#include <map>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/Renderer/OpenGL/OpenGLEnums.hpp"

class ShaderProgram;

class Sampler2D {
public:
	//STRUCTORS
	Sampler2D();
	Sampler2D(eRenderEnum minFilter, eRenderEnum magFilter, eRenderEnum uwrap, eRenderEnum vwrap);

	//INTERFACE
	void AddTexture(const std::string& nameInShader, Texture* texture);
	void BindTextures(uint programID) const;

	//GETTERS SETTERS
	Texture* GetTextureByName(const std::string& textureNameInShader);
	uint GetSamplerID() const;

private:
	uint m_samplerID;
	std::map<std::string, Texture*> m_texturesToBind;
};