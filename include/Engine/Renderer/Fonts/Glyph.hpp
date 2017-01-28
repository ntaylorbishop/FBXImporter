#pragma once

#include <map>
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/AABB2.hpp"

class Glyph {
public:
	//STRUCTORS
	Glyph();
	Glyph(unsigned char id, Vector2 spriteSheetCoords, float height, Vector2 offset, float xAdvance);

	//GETTERS
	char GetID() const;
	AABB2 GetTextureCoords(const Vector2& sizeOfImage) const;
	float GetHeight() const;
	float GetWidth() const;
	Vector2 GetOffset() const;
	float GetXAdvance() const;
	int GetFromKerningList(unsigned char id);

	//SETTERS
	void SetID(unsigned char id);
	void SetSpriteSheetCoordsX(float x);
	void SetSpriteSheetCoordsY(float y);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetOffsetX(float xOffset);
	void SetOffsetY(float yOffset);
	void SetXAdvance(float xAdvance);
	void AddToKerningList(std::pair<unsigned char, int> idAndAmount);

private:
	unsigned char m_ID;
	Vector2 m_pixelCoords;
	float m_width;
	float m_height;
	Vector2 m_offset;
	float m_xAdvance;

	std::map<unsigned char, int> m_kernings;
};