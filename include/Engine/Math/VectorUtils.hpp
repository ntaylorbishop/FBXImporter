#pragma once

#include <stdlib.h>
#include <string>
#include <math.h>

#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector3.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"

float VectorToAngle(const IntVector2& point);
float VectorToAngle(const Vector2& point);
float VectorToAngle(const IntVector3& point);
float VectorToAngle(const Vector3& point);

float DotProduct(const IntVector2& v1, const IntVector2& v2);
float DotProduct(const Vector2& v1, const Vector2& v2);
float DotProduct(const IntVector3& v1, const IntVector3& v2);
float DotProduct(const Vector3& v1, const Vector3& v2);
float DotProduct(const Vector4& v1, const Vector4& v2);


Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);

Vector2 IncreaseVectorByLength(const Vector2& v, float length);
Vector3 IncreaseVectorByLength(const Vector3& v, float length);

IntVector2 FindNormalToLine(const IntVector2& p1, const IntVector2& p2, bool positiveHalfSpace);
Vector2 FindNormalToLine(const Vector2& p1, const Vector2& p2, bool positiveHalfSpace);

std::string ToString(const IntVector2& v);
std::string ToString(const Vector2& v);
std::string ToString(const IntVector3& v);
std::string ToString(const Vector3& v);