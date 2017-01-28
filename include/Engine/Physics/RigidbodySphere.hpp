#pragma once

#include "Engine/Physics/Rigidbody.hpp"

class RigidbodySphere : public Rigidbody {
public:
	//STRUCTORS
	RigidbodySphere();

	//UPDATE
	void Update(float deltaSeconds);

private:
	//INHERITED
	//Matrix4 m_model;
	//float m_timeStep;
};