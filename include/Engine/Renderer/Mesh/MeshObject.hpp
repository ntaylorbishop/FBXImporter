#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Engine/Renderer/Material/Material.hpp"

class MeshObject {
public:
	//STRUCTORS INIT
	MeshObject();
	void AddMeshAndMaterial(Mesh* mesh, Material* material);

	//RENDER
	void Render() const;

	//UPDATERS
	void Translate(const Matrix4& model);

private:
	std::vector<Mesh*> m_meshes;
	std::vector<Material*> m_materials;

	MeshRenderer m_meshRenderer;
};