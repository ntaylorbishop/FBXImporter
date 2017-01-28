#pragma once

#include <vector>

#include "Engine/Renderer/Vertex/Vertex.hpp"
#include "Engine/Renderer/OpenGL/OpenGLEnums.hpp"
#include "Engine/General/Core/EngineCommon.hpp"

enum VertexType {
	VTYPE_VERTEX = 0,
	VTYPE_TEXTUREDVERTEX,
	VTYPE_TEXTUREDVERTEX_TBN
};

//---------------------------------------------------------------------------------------------------------------------------
//VERTEX ATTRIBUTE
//---------------------------------------------------------------------------------------------------------------------------
struct VertexAttribute {
	const char* name;
	unsigned int count;
	eRenderEnum type;
	eRenderEnum normalize;
	size_t stride;
	size_t offset;
};

//---------------------------------------------------------------------------------------------------------------------------
//VERTEX DEFINITION
//---------------------------------------------------------------------------------------------------------------------------
class VertexDefinition {
public:
	static void InitializeVertexDefinitions();

	uint GetVertexSize() const;
	uint GetStride() const;
	const std::vector<VertexAttribute>* GetAllAttributes() const;

	VertexType GetVertexType() const;

	static VertexDefinition VERTEX;
	static VertexDefinition TEXTUREDVERTEX;
	static VertexDefinition TEXTUREDVERTEX_TBN;
	static VertexDefinition TEXTUREDVERTEX_N;
	static VertexDefinition TEXTUREDVERTEX_TBNBN;

private:
	VertexDefinition();
	void SetAttribute(const char* name, unsigned int numElements, eRenderEnum primitiveType, eRenderEnum isNormalized, size_t size, size_t offset);

private:
	std::vector<VertexAttribute> m_attribs;
	VertexType m_vertexType;
};