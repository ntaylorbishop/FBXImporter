#pragma once

#include <math.h>
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class Vector3 {
public:
	//STRUCTORS
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);

	float Length() const;
	void Normalize();

	//OPERATOR OVERLOADS
	Vector3 operator-();

	friend Vector3 operator+(const Vector3 &p1, const Vector3 &p2);
	friend Vector3 operator-(const Vector3 &p1, const Vector3 &p2);

	Vector3 operator+=(const Vector3 &p);
	Vector3 operator-=(const Vector3 &p);
	Vector3 operator+=(const int scalar);
	Vector3 operator-=(const int scalar);

	friend Vector3 operator+(const Vector3 &p1, const float scalar);
	friend Vector3 operator-(const Vector3 &p1, const float scalar);
	friend Vector3 operator+(const float scalar, const Vector3 &p1);
	friend Vector3 operator-(const float scalar, const Vector3 &p1);

	friend Vector3 operator*(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v, const float scalar);
	friend Vector3 operator*(const float scalar, const Vector3& v);
	friend Vector3 operator/(const Vector3& v, const float scalar);

	Vector3 operator*=(const Vector3& other);
	Vector3 operator*=(const float scalar);

	//CONDITIONAL OPERATOSR
	bool operator<(const Vector3 &other) const;
	bool operator>(const Vector3 &other) const;
	bool operator<=(const Vector3 &other) const;
	bool operator>=(const Vector3 &other) const;
	bool operator==(const Vector3 &other) const;
	bool operator!=(const Vector3 &other) const;

public:
	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 UNIT_VECTOR_X;
	static const Vector3 UNIT_VECTOR_Y;
	static const Vector3 UNIT_VECTOR_Z;
	static const Vector3 RIGHT;
	static const Vector3 UP;
	static const Vector3 FORWARD;


public:
	float x;
	float y;
	float z;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float Vector3::Length() const {
	return sqrt(x * x + y * y + z * z);
}
inline void Vector3::Normalize() {
	float length = sqrt(x * x + y * y + z * z);

	if (length != 0.f) {
		x = x / length;
		y = y / length;
		z = z / length;
	}
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline Vector3 Vector3::operator-() {
	x = -x;
	y = -y;
	z = -z; 
	return *this;
}

inline Vector3 operator+(const Vector3 &p1, const Vector3 &p2) {
	return Vector3(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}
inline Vector3 operator-(const Vector3 &p1, const Vector3 &p2) {
	return Vector3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

inline Vector3 Vector3::operator+=(const Vector3 &p) {
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}
inline Vector3 Vector3::operator-=(const Vector3 &p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}
inline Vector3 Vector3::operator+=(const int scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}
inline Vector3 Vector3::operator-=(const int scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

inline Vector3 operator+(const Vector3 &p1, const float scalar) {
	return Vector3(p1.x + scalar, p1.y + scalar, p1.z + scalar);
}
inline Vector3 operator-(const Vector3 &p1, const float scalar) {
	return Vector3(p1.x - scalar, p1.y - scalar, p1.z - scalar);
}
inline Vector3 operator+(const float scalar, const Vector3 &p1) {
	return Vector3(p1.x + scalar, p1.y + scalar, p1.z + scalar);
}
inline Vector3 operator-(const float scalar, const Vector3 &p1) {
	return Vector3(p1.x - scalar, p1.y - scalar, p1.z - scalar);
}

inline Vector3 operator*(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline Vector3 operator*(const Vector3& v, const float scalar) {
	return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
}
inline Vector3 operator*(const float scalar, const Vector3& v) {
	return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
}
inline Vector3 operator/(const Vector3& v, const float scalar) {
	if (scalar == 0.f) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a Vector3 by zero", SEVERITY_FATAL);
		return Vector3(0.f, 0.f, 0.f);
	}
	else
		return Vector3(v.x / scalar, v.y / scalar, v.z / scalar);
}

inline Vector3 Vector3::operator*=(const Vector3& other) {
	return Vector3(x * other.x, y * other.y, z * other.z);
}
inline Vector3 Vector3::operator*=(const float scalar) {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool Vector3::operator<(const Vector3 &other) const {
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
inline bool Vector3::operator>(const Vector3 &other) const {
	return !(*this < other);
}
inline bool Vector3::operator<=(const Vector3 &other) const {
	if (x <= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector3::operator>=(const Vector3 &other) const {
	if (x >= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector3::operator==(const Vector3 &other) const {
	if (x == other.x && y == other.y && z == other.z) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Vector3::operator!=(const Vector3 &other) const {
	return !(*this == other);
}