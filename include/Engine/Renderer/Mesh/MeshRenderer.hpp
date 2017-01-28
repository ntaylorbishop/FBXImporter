#pragma once

#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"

class MeshRenderer {
public:
	//STRUCTORS
	MeshRenderer();

	//UPDATE RENDER
	void RenderMeshWithMaterial(const Mesh& mesh, Material* mat) const;

private:
	void UpdateModelUnifomInMaterial(const Mesh& mesh, Material* mat) const;
	
private:
	int m_vaoID;
};