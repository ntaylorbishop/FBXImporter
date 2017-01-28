#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <string>
#include <map>

#include "Engine/Renderer/OpenGL/OpenGLExtensions.hpp"
#include "Engine/Math/IntVector2.hpp"

enum eTextureFormat {
	eTextureFormat_RGBA8,
	eTextureFormat_D24S8,
};

using namespace std;
class Texture {
public:
	static Texture* Texture::CreateOrGetTexture(int blankTextureID, int width, int height, eTextureFormat format);
	static Texture* Texture::CreateOrGetTexture(const string& imageFilePath);
	static Texture* Texture::GetTextureByName(const string& imageFilePath);

	int GetTextureID() const;

	int GetHeight() const;
	int GetWidth() const;
	
private:
	//TODO: Fix this, it leaks memory
	Texture(int width, int height, eTextureFormat format);
	Texture(const string& imageFilePath);

	static map<string, Texture*> s_textureRegistry;
	static map<int, Texture*> s_blankTextureRegistry;

	GLuint m_openglTextureID;
	IntVector2 m_texelSize;
};
