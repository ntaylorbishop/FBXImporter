#pragma once

#include "Engine/Math/Vector3.hpp"

class AABB3 {
public:
	AABB3() : mins(), maxs() {}
	AABB3(const Vector3& mins, const Vector3& maxs) {
		this->mins = mins;
		this->maxs = maxs;
	}

	Vector3 mins;
	Vector3 maxs;
};