#pragma once

#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/IntVector4.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Renderer/General/RGBA.hpp"

class TexturedVertex {
public:
	TexturedVertex();
	TexturedVertex(const Vector3& pos, const RGBA& col, const Vector2& tex);

	Vector3 m_position;
	RGBA m_color;
	Vector2 m_texCoords;
};

class Vertex {
public:
	Vertex();
	Vertex(const Vector3& pos, const RGBA& col);

	Vector3 m_position;
	RGBA m_color;
};

class TexturedVertex_TBN {
public:
	TexturedVertex_TBN();
	TexturedVertex_TBN(const Vector3& pos, const RGBA& col, const Vector2& tex, const Vector3& tangent, const Vector3& bitangent);

	Vector3 m_position;
	RGBA m_color;
	Vector2 m_texCoords;
	Vector3 m_tangent;
	Vector3 m_bitangent;
};

class TexturedVertex_N {
public:
	TexturedVertex_N();
	TexturedVertex_N(const Vector3& pos, const RGBA& col, const Vector2& tex, const Vector3& normal);

	Vector3 m_position;
	RGBA m_color;
	Vector2 m_texCoord;
	Vector3 m_normal;
};

class TexturedVertex_TBNBN {
public:
	TexturedVertex_TBNBN();
	TexturedVertex_TBNBN(const Vector3& pos, const RGBA& col, 
		const Vector2& tex, const Vector3& tangent, const Vector3& bitangent, const Vector4& boneWeights, const IntVector4& boneInds);

	Vector3 m_position;
	RGBA m_color;
	Vector2 m_texCoords;
	Vector3 m_tangent;
	Vector3 m_bitangent;

	Vector4 m_boneWeights;
	IntVector4 m_boneInds;
};