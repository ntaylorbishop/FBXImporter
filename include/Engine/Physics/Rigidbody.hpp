#pragma once

#include "Engine/Math/Matrix4.hpp"

const float MAX_DELTA_TIMESTEP = 0.3f;

class Rigidbody {
public:
	Rigidbody();

	virtual void Update(float deltaSeconds);

private:
	Matrix4 m_model;
	float m_timeStep;
};