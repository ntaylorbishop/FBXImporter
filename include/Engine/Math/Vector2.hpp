#pragma once

#include <math.h>
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class IntVector2;

class Vector2 {
public:
	//STRUCTORS
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);

	IntVector2 ToIntVector2();

	float Length() const;
	void Normalize();

	//OPERATOR OVERLOADS
	Vector2 operator-();

	friend Vector2 operator+(const Vector2 &p1, const Vector2 &p2);
	friend Vector2 operator-(const Vector2 &p1, const Vector2 &p2);

	Vector2& operator+=(const Vector2 &p);
	Vector2 operator-=(const Vector2 &p);
	Vector2 operator+=(const int scalar);
	Vector2 operator-=(const int scalar);

	friend Vector2 operator+(const Vector2 &p1, const float scalar);
	friend Vector2 operator-(const Vector2 &p1, const float scalar);
	friend Vector2 operator+(const float scalar, const Vector2 &p1);
	friend Vector2 operator-(const float scalar, const Vector2 &p1);

	friend Vector2 operator*(const Vector2& v1, const Vector2& v2);
	friend Vector2 operator*(const Vector2& v, const float scalar);
	friend Vector2 operator*(const float scalar, const Vector2& v);
	friend Vector2 operator/(const Vector2& v, const float scalar);

	Vector2 operator*=(const Vector2& other);
	Vector2 operator*=(const float scalar);

	//CONDITIONAL OPERATORS
	bool operator<(const Vector2 &other) const;
	bool operator>(const Vector2 &other) const;
	bool operator<=(const Vector2 &other) const;
	bool operator>=(const Vector2 &other) const;
	bool operator==(const Vector2 &other) const;
	bool operator!=(const Vector2 &other) const;

public:
	static const Vector2 UNIT_VECTOR_X;
	static const Vector2 UNIT_VECTOR_Y;
	static const Vector2 ZERO;
	static const Vector2 ONE;
	
	static const Vector2 TEXCOORD_TOP_LEFT;
	static const Vector2 TEXCOORD_TOP_RIGHT;
	static const Vector2 TEXCOORD_BOTTOM_RIGHT;
	static const Vector2 TEXCOORD_BOTTOM_LEFT;

public:
	float x;
	float y;
};


//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float Vector2::Length() const {
	return sqrt(x * x + y * y);
}
inline void Vector2::Normalize() {
	float length = sqrt(x * x + y * y);
	x = x / length;
	y = y / length;
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline Vector2 Vector2::operator-() {
	x = -x;
	y = -y;
}

inline Vector2 operator+(const Vector2 &p1, const Vector2 &p2) {
	return Vector2(p1.x + p2.x, p1.y + p2.y);
}
inline Vector2 operator-(const Vector2 &p1, const Vector2 &p2) {
	return Vector2(p1.x - p2.x, p1.y - p2.y);
}

inline Vector2& Vector2::operator+=(const Vector2 &p) {
	x += p.x;
	y += p.y;
	return *this;
	//FIX THIS WITH OTHER VECTORS
}
inline Vector2 Vector2::operator-=(const Vector2 &p) {
	return Vector2(x - p.x, y - p.y);
}
inline Vector2 Vector2::operator+=(const int scalar) {
	return Vector2(x + scalar, y + scalar);
}
inline Vector2 Vector2::operator-=(const int scalar) {
	return Vector2(x - scalar, y - scalar);
}

inline Vector2 operator+(const Vector2 &p1, const float scalar) {
	return Vector2(p1.x + scalar, p1.y + scalar);
}
inline Vector2 operator-(const Vector2 &p1, const float scalar) {
	return Vector2(p1.x - scalar, p1.y - scalar);
}
inline Vector2 operator+(const float scalar, const Vector2 &p1) {
	return Vector2(p1.x + scalar, p1.y + scalar);
}
inline Vector2 operator-(const float scalar, const Vector2 &p1) {
	return Vector2(p1.x - scalar, p1.y - scalar);
}

inline Vector2 operator*(const Vector2& v1, const Vector2& v2) {
	return Vector2(v1.x * v2.x, v1.y * v2.y);
}
inline Vector2 operator*(const Vector2& v, const float scalar) {
	return Vector2(scalar * v.x, scalar * v.y);
}
inline Vector2 operator*(const float scalar, const Vector2& v) {
	return Vector2(scalar * v.x, scalar * v.y);
}
inline Vector2 operator/(const Vector2& v, const float scalar) {
	if (scalar == 0.f) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a Vector2 by zero", SEVERITY_FATAL);
		return Vector2(0.f, 0.f);
	}
	else
		return Vector2(v.x / scalar, v.y / scalar);
}

inline Vector2 Vector2::operator*=(const Vector2& other) {
	return Vector2(x * other.x, y * other.y);
}
inline Vector2 Vector2::operator*=(const float scalar) {
	return Vector2(x * scalar, y * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool Vector2::operator<(const Vector2 &other) const {
	if (x < other.x) {
		return true;
	}
	else if (x > other.x) {
		return false;
	}
	else if (x == other.x) {
		if (y < other.y) {
			return true;
		}
		else {
			return false;
		}
	}
}
inline bool Vector2::operator>(const Vector2 &other) const {
	return !(*this < other);
}
inline bool Vector2::operator<=(const Vector2 &other) const {
	if (x <= other.x) {
		return true;
	}
	else
		return false;
}
inline bool Vector2::operator>=(const Vector2 &other) const {
	if (x >= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector2::operator==(const Vector2 &other) const {
	if (this->x == other.x && this->y == other.y)
		return true;
	else
		return false;
}
inline bool Vector2::operator!=(const Vector2 &other) const {
	return !(*this == other);
}