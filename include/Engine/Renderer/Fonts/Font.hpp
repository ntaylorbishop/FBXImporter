#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Engine/General/Utils/StringUtils.hpp"
#include "Engine/General/Utils/FileUtils.hpp"
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/Renderer/Fonts/Glyph.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"

class Font {
public:
	static Font* Font::CreateOrGetFont(std::string fontName);

	void DrawText2D(const Vector2& position, const std::string& str, float scale, const RGBA& color = RGBA::WHITE);
	float GetXAdvanceOfGlyph(unsigned char glyphChar, float scale);
	Glyph* GetGlyphForCharacter(unsigned char glyphChar);
	float GetLineHeight();
	float GetWidthOfString(std::string str, float scale);

private:
	Font(std::string fontName);
	void LoadGlyphsFromFile();
	void ParseBufferIntoGlpyhs(std::vector<unsigned char> buffer);

private:
	static map<std::string, Font*> s_fontRegistry;
	
	std::string m_fontName;
	Texture* m_texture;
	std::map<unsigned char, Glyph*> m_glyphs;
	Vector2 m_textureScale;
	float m_lineHeight;
};