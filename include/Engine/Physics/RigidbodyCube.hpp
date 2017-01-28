#pragma once

#include "Engine/Physics/Rigidbody.hpp"
#include "Engine/Physics/Constraint.hpp"

class RigidbodyCube : public Rigidbody {
public:
	//STRUCTORS
	RigidbodyCube(const Vector3& center, const Vector3& scale);

	//UPDATE
	void Update(float deltaSeconds);

private:

};