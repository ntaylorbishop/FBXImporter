#pragma once

#include <math.h>

#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/MathUtils.hpp"

class PolarCoords {
public:
	PolarCoords();
	PolarCoords(float radius, float theta);
	PolarCoords(IntVector2 v);
	PolarCoords(Vector2 v);

	Vector2 toVector2_InRadians();
	Vector2 toVector2_InDegrees();

	//Member data
	float radius;
	float theta;
};