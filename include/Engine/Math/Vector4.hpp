#pragma once

#include <math.h>
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class Vector4 {
public:
	//STRUCTORS
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& other);

	float Length() const;
	void Normalize();

	//OPERATOR OVERLOADS
	Vector4 operator-();

	friend Vector4 operator+(const Vector4 &p1, const Vector4 &p2);
	friend Vector4 operator-(const Vector4 &p1, const Vector4 &p2);

	Vector4 operator+=(const Vector4 &p);
	Vector4 operator-=(const Vector4 &p);
	Vector4 operator+=(const int scalar);
	Vector4 operator-=(const int scalar);

	friend Vector4 operator+(const Vector4 &p1, const float scalar);
	friend Vector4 operator-(const Vector4 &p1, const float scalar);
	friend Vector4 operator+(const float scalar, const Vector4 &p1);
	friend Vector4 operator-(const float scalar, const Vector4 &p1);

	friend Vector4 operator*(const Vector4& v1, const Vector4& v2);
	friend Vector4 operator*(const Vector4& v, const float scalar);
	friend Vector4 operator*(const float scalar, const Vector4& v);
	friend Vector4 operator/(const Vector4& v, const float scalar);

	Vector4 operator*=(const Vector4& other);
	Vector4 operator*=(const float scalar);

	//CONDITIONAL OPERATOSR
	bool operator<(const Vector4 &other) const;
	bool operator>(const Vector4 &other) const;
	bool operator<=(const Vector4 &other) const;
	bool operator>=(const Vector4 &other) const;
	bool operator==(const Vector4 &other) const;
	bool operator!=(const Vector4 &other) const;

public:
	static const Vector4 ZERO;
	static const Vector4 ONE;
	static const Vector4 UNIT_VECTOR_X;
	static const Vector4 UNIT_VECTOR_Y;
	static const Vector4 UNIT_VECTOR_Z;
	static const Vector4 UNIT_VECTOR_W;

public:
	float x;
	float y;
	float z;
	float w;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float Vector4::Length() const {
	return sqrt(x * x + y * y + z * z + w * w);
}
inline void Vector4::Normalize() {
	float length = sqrt(x * x + y * y + z * z + w * w);

	if (length != 0.f) {
		x = x / length;
		y = y / length;
		z = z / length;
		w = w / length;
	}
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline Vector4 Vector4::operator-() {
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

inline Vector4 operator+(const Vector4 &p1, const Vector4 &p2) {
	return Vector4(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w + p2.w);
}
inline Vector4 operator-(const Vector4 &p1, const Vector4 &p2) {
	return Vector4(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, p1.w - p2.w);
}

inline Vector4 Vector4::operator+=(const Vector4 &p) {
	x += p.x;
	y += p.y;
	z += p.z;
	w += p.w;
	return *this;
}
inline Vector4 Vector4::operator-=(const Vector4 &p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
	w -= p.w;
	return *this;
}
inline Vector4 Vector4::operator+=(const int scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	return *this;
}
inline Vector4 Vector4::operator-=(const int scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
}

inline Vector4 operator+(const Vector4 &p1, const float scalar) {
	return Vector4(p1.x + scalar, p1.y + scalar, p1.z + scalar, p1.w + scalar);
}
inline Vector4 operator-(const Vector4 &p1, const float scalar) {
	return Vector4(p1.x - scalar, p1.y - scalar, p1.z - scalar, p1.w - scalar);
}
inline Vector4 operator+(const float scalar, const Vector4 &p1) {
	return Vector4(p1.x + scalar, p1.y + scalar, p1.z + scalar, p1.w + scalar);
}
inline Vector4 operator-(const float scalar, const Vector4 &p1) {
	return Vector4(p1.x - scalar, p1.y - scalar, p1.z - scalar, p1.w - scalar);
}

inline Vector4 operator*(const Vector4& v1, const Vector4& v2) {
	return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}
inline Vector4 operator*(const Vector4& v, const float scalar) {
	return Vector4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}
inline Vector4 operator*(const float scalar, const Vector4& v) {
	return Vector4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}
inline Vector4 operator/(const Vector4& v, const float scalar) {
	if (scalar == 0.f) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a Vector4 by zero", SEVERITY_FATAL);
		return Vector4(0.f, 0.f, 0.f, 0.f);
	}
	else
		return Vector4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

inline Vector4 Vector4::operator*=(const Vector4& other) {
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}
inline Vector4 Vector4::operator*=(const float scalar) {
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool Vector4::operator<(const Vector4 &other) const {
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
		else if (y > other.y) {
			return false;
		}
		else if (y == other.y) {
			if (z < other.z) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
inline bool Vector4::operator>(const Vector4 &other) const {
	return !(*this < other);
}
inline bool Vector4::operator<=(const Vector4 &other) const {
	if (x <= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector4::operator>=(const Vector4 &other) const {
	if (x >= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector4::operator==(const Vector4 &other) const {
	if (x == other.x && y == other.y && z == other.z && w == other.w) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector4::operator!=(const Vector4 &other) const {
	return !(*this == other);
}