#pragma once

#include <map>
#include <string>
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/AABB2.hpp"

typedef AABB2 SpriteCoords;
typedef Vector2 TexCoords;


using namespace std;
class SpriteSheet {
public:
	static SpriteSheet* SpriteSheet::CreateOrGetSpriteSheet(const IntVector2& tileSize, const char* imageFilePath);

	AABB2 GetTexCoordsForSpriteCoords(const IntVector2& spriteCoords) const;
	const Texture* GetTexture() const;
	AABB2 GetTexCoordsForSpriteIndex(int spriteIndex) const; // mostly for sprite animations
	int GetNumSprites() const;

private:
	SpriteSheet(const IntVector2& tileSize, const char* imageFilePath);

	static map<const char*, SpriteSheet*> s_spriteSheetRegistry;

	Vector2 m_texCoordsPerTile;
	IntVector2 m_tileSize;
	const Texture* m_spriteSheetTexture;
};