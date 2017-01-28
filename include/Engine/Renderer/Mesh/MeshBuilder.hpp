#pragma once

#include "Engine/General/Core/EngineCommon.hpp"

#include "Engine/General/Utils/FileUtils/FileBinaryWriter.hpp"
#include "Engine/General/Utils/FileUtils/FileBinaryReader.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Mesh/MeshObject.hpp"

class MeshBuilder {
public:
	//STRUCTORS
	MeshBuilder();
	~MeshBuilder();

	//BUILDING
	void AddMesh();
	void AddVertex(TexturedVertex_TBNBN vert);
	void AddInd(uint16_t ind);
	void CloseMesh();

	//AFTER BUILDING
	void Reduce();

	//READ WRITE
	static void WriteMeshToFile(Mesh* mesh, const String& path, const String& filename);
	static Mesh* ReadMeshFromFile(Mesh* mesh, const String& path, const String& filename);

	//GETTERS SETTERS
	Mesh* GetMasterMesh();
	uint GetNumMeshes() const;

private:
	Mesh* m_currMesh;
	std::vector<Mesh*> m_meshes;
	Mesh* m_masterMesh;

	FileBinaryWriter m_fileWriter;
	FileBinaryReader m_fileReader;
};