#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/Math.hpp"

class TheCamera;
extern TheCamera* g_theCamera;

class TheCamera {
public:
	//STRUCTORS
	TheCamera();
	TheCamera(Vector3 position, float roll, float pitch, float yaw);
	void Initialization();

	//UPDATE RENDER
	void Update(float deltaSeconds);

	//MOVEMENT VECTORS
	Vector3 GetForwardXYZ() const;
	Vector3 GetForwardXY() const;
	Vector3 GetLeftXY() const;

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;

public:
	Vector3 m_position;
	float m_rollAboutY;
	float m_pitchAboutX;
	float m_yawAboutZ;

	Matrix4 m_view;
	Matrix4 m_projection;
};