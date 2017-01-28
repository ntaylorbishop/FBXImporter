#pragma once

#include <stdint.h>
#include <vector>
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Vertex/Vertex.hpp"
#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"

//ASSUMING ALL MESHES ARE DYNAMIC DRAWS FOR NOW
//---------------------------------------------------------------------------------------------------------------------------
//STRUCTS
//---------------------------------------------------------------------------------------------------------------------------
struct DrawInstruction {
	unsigned int primitiveType;
	unsigned int startIndex;
	unsigned int count;
	bool useIndexBuffer;
};

//---------------------------------------------------------------------------------------------------------------------------
//MESH CLASS
//---------------------------------------------------------------------------------------------------------------------------
class Mesh {
public:
	//STRUCTORS
	Mesh();
	Mesh(const VertexDefinition& vertexDef);
	~Mesh();

	//Add vertex
	void AddVertex(Vertex vert);
	void AddVertex(TexturedVertex vert);
	void AddVertex(TexturedVertex_TBN vert);
	void AddVertex(TexturedVertex_N vert);
	void AddVertex(TexturedVertex_TBNBN vert);

	void AddInd(uint16_t ind);

	//GETTERS SETTERS
	void UpdateMesh();
	void UpdateMeshForNormals();
	void UpdateMesh(const std::vector<TexturedVertex_TBN>& verts, const std::vector<uint16_t>& inds);
	void UpdateMesh(const std::vector<TexturedVertex>& verts, const std::vector<uint16_t>& inds);
	void UpdateMesh(const std::vector<Vertex>& verts, const std::vector<uint16_t>& inds);
	void UpdateMesh(const std::vector<TexturedVertex_TBN>& verts);
	void UpdateMesh(const std::vector<TexturedVertex>& verts);
	void UpdateMesh(const std::vector<uint16_t>& inds);

	void UpdateMeshInds(const std::vector<uint16_t>& inds);

	void UpdateModel(const Matrix4& model);

	void ChangePosition(const Vector3& position);

	int GetVboID() const;
	int GetIboID() const;
	Matrix4 GetModel() const;

	VertexDefinition GetVertexDefinition() const;

	//DRAWING
	void BindMesh() const;
	void UnbindMesh() const;
	void DrawMesh() const;

public:
	VertexDefinition m_vertexDef;
	std::vector<DrawInstruction> m_drawInstructions;
	bool m_usesInds = true;

public:
	int m_vboID;
	int m_iboID;

	std::vector<TexturedVertex_TBNBN> m_texturedVertsTBNBN;
	std::vector<TexturedVertex_N> m_texturedVertsN;
	std::vector<TexturedVertex_TBN> m_texturedVertsTBN;
	std::vector<TexturedVertex> m_texturedVerts;
	std::vector<Vertex> m_verts;
	std::vector<uint16_t> m_inds;

	bool m_drawStatic;

	Matrix4 m_model;

};