#pragma once

#define _USE_MATH_DEFINES

#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Game/TheCamera.hpp"
#include "Game/GameCommon.hpp"
#include "Game/MaterialManager.hpp"

class Sphere {
public:
	//STRUCTORS
	Sphere();
	Sphere(float radius, const Vector3& position);

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

private:
	void CreateMesh(float radius);

	Vector3 DebugExtendVector3(const Vector3& vec);

private:
	float m_radius;
	Vector3 m_position;

	MeshRenderer m_meshRenderer;
	Mesh m_mesh;
	Material* m_material;

};