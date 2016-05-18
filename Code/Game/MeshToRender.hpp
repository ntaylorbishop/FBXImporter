#pragma once

#define _USE_MATH_DEFINES

#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Material/Shaders/Shader.hpp"
#include "Engine/Renderer/Material/Shaders/ShaderProgram.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Game/TheCamera.hpp"
#include "Game/GameCommon.hpp"
#include "Game/LightSystem.hpp"
#include "Game/MaterialManager.hpp"

class MeshToRender {
public:
	//STRUCTORS
	MeshToRender();
	MeshToRender(const Vector3& position);

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	void SwapToCubeMesh();

	MeshRenderer m_meshRenderer;
	Mesh* m_mesh;
	Material* m_material;

private:
	void SwitchToCubeMesh();
};