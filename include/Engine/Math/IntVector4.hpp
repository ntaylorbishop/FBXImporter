#pragma once

#include <cmath>
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class IntVector4 {
public:
	//STRUCTORS
	IntVector4();
	IntVector4(int x, int y, int z, int w);
	IntVector4(const IntVector4& other);

	float Length() const;

	//OPERATOR OVERLOADS
	IntVector4 operator-();

	friend IntVector4 operator+(const IntVector4 &p1, const IntVector4 &p2);
	friend IntVector4 operator-(const IntVector4 &p1, const IntVector4 &p2);

	IntVector4 operator+=(const IntVector4 &p);
	IntVector4 operator-=(const IntVector4 &p);
	IntVector4 operator+=(const int scalar);
	IntVector4 operator-=(const int scalar);

	friend IntVector4 operator+(const IntVector4 &p1, const int scalar);
	friend IntVector4 operator-(const IntVector4 &p1, const int scalar);
	friend IntVector4 operator+(const int scalar, const IntVector4 &p1);
	friend IntVector4 operator-(const int scalar, const IntVector4 &p1);

	friend IntVector4 operator*(const IntVector4& v1, const IntVector4& v2);
	friend IntVector4 operator*(const IntVector4& v, const int scalar);
	friend IntVector4 operator*(const int scalar, const IntVector4& v);
	friend IntVector4 operator/(const IntVector4& v, const int scalar);

	IntVector4 operator*=(const IntVector4& other);
	IntVector4 operator*=(const int scalar);

	//CONDITIONAL OPERATOSR
	bool operator<(const IntVector4 &other) const;
	bool operator>(const IntVector4 &other) const;
	bool operator<=(const IntVector4 &other) const;
	bool operator>=(const IntVector4 &other) const;
	bool operator==(const IntVector4 &other) const;
	bool operator!=(const IntVector4 &other) const;

public:
	static const IntVector4 ZERO;
	static const IntVector4 ONE;
	static const IntVector4 UNIT_VECTOR_X;
	static const IntVector4 UNIT_VECTOR_Y;
	static const IntVector4 UNIT_VECTOR_Z;
	static const IntVector4 UNIT_VECTOR_W;

public:
	int x;
	int y;
	int z;
	int w;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float IntVector4::Length() const {
	return sqrtf((float)x * (float)x + (float)y * (float)y + (float)z * (float)z + (float)w * (float)w);
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline IntVector4 IntVector4::operator-() {
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

inline IntVector4 operator+(const IntVector4 &p1, const IntVector4 &p2) {
	return IntVector4(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w + p2.w);
}
inline IntVector4 operator-(const IntVector4 &p1, const IntVector4 &p2) {
	return IntVector4(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, p1.w - p2.w);
}

inline IntVector4 IntVector4::operator+=(const IntVector4 &p) {
	x += p.x;
	y += p.y;
	z += p.z;
	w += p.w;
	return *this;
}
inline IntVector4 IntVector4::operator-=(const IntVector4 &p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
	w -= p.w;
	return *this;
}
inline IntVector4 IntVector4::operator+=(const int scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	return *this;
}
inline IntVector4 IntVector4::operator-=(const int scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
}

inline IntVector4 operator+(const IntVector4 &p1, const int scalar) {
	return IntVector4(p1.x + scalar, p1.y + scalar, p1.z + scalar, p1.w + scalar);
}
inline IntVector4 operator-(const IntVector4 &p1, const int scalar) {
	return IntVector4(p1.x - scalar, p1.y - scalar, p1.z - scalar, p1.w - scalar);
}
inline IntVector4 operator+(const int scalar, const IntVector4 &p1) {
	return IntVector4(p1.x + scalar, p1.y + scalar, p1.z + scalar, p1.w + scalar);
}
inline IntVector4 operator-(const int scalar, const IntVector4 &p1) {
	return IntVector4(p1.x - scalar, p1.y - scalar, p1.z - scalar, p1.w - scalar);
}

inline IntVector4 operator*(const IntVector4& v1, const IntVector4& v2) {
	return IntVector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}
inline IntVector4 operator*(const IntVector4& v, const int scalar) {
	return IntVector4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}
inline IntVector4 operator*(const int scalar, const IntVector4& v) {
	return IntVector4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}
inline IntVector4 operator/(const IntVector4& v, const int scalar) {
	if (scalar == 0) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a IntVector4 by zero", SEVERITY_FATAL);
		return IntVector4(0, 0, 0, 0);
	}
	else
		return IntVector4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

inline IntVector4 IntVector4::operator*=(const IntVector4& other) {
	return IntVector4(x * other.x, y * other.y, z * other.z, w * other.w);
}
inline IntVector4 IntVector4::operator*=(const int scalar) {
	return IntVector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool IntVector4::operator<(const IntVector4 &other) const {
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
inline bool IntVector4::operator>(const IntVector4 &other) const {
	return !(*this < other);
}
inline bool IntVector4::operator<=(const IntVector4 &other) const {
	if (x <= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool IntVector4::operator>=(const IntVector4 &other) const {
	if (x >= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool IntVector4::operator==(const IntVector4 &other) const {
	if (x == other.x && y == other.y && z == other.z && w == other.w) {
		return true;
	}
	else {
		return false;
	}
}
inline bool IntVector4::operator!=(const IntVector4 &other) const {
	return !(*this == other);
}