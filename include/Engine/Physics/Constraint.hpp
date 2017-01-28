#pragma once

#include "Engine/Math/Vector3.hpp"

class Constraint {
public:
	Constraint(Vector3* p1, Vector3* p2);

	void SatisfyConstraints();

public:
	Vector3* m_p1;
	Vector3* m_p2;

private:
	float m_restDistance;
};