#pragma once
#include <math.h>
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class IntVector3 {
public:
	IntVector3();
	IntVector3(int x, int y, int z);
	IntVector3(const IntVector3& other);

	float Length() const;

	//OPERATOR OVERLOADS
	IntVector3 operator-();

	friend IntVector3 operator+(const IntVector3 &p1, const IntVector3 &p2);
	friend IntVector3 operator-(const IntVector3 &p1, const IntVector3 &p2);

	IntVector3 operator+=(const IntVector3 &p);
	IntVector3 operator-=(const IntVector3 &p);
	IntVector3 operator+=(const int scalar);
	IntVector3 operator-=(const int scalar);

	friend IntVector3 operator+(const IntVector3 &p1, const int scalar);
	friend IntVector3 operator-(const IntVector3 &p1, const int scalar);
	friend IntVector3 operator+(const int scalar, const IntVector3 &p1);
	friend IntVector3 operator-(const int scalar, const IntVector3 &p1);

	friend IntVector3 operator*(const IntVector3& v1, const IntVector3& v2);
	friend IntVector3 operator*(const IntVector3& v, const int scalar);
	friend IntVector3 operator*(const int scalar, const IntVector3& v);
	friend IntVector3 operator/(const IntVector3& v, const int scalar);

	inline IntVector3 operator*=(const IntVector3& other);
	inline IntVector3 operator*=(const int scalar);

	//CONDITIONAL OPERATORS
	bool operator<(const IntVector3 &other) const;
	bool operator>(const IntVector3 &other) const;
	bool operator<=(const IntVector3 &other) const;
	bool operator>=(const IntVector3 &other) const;
	bool operator==(const IntVector3 &other) const;
	bool operator!=(const IntVector3 &other) const;

public:
	int x;
	int y;
	int z;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float IntVector3::Length() const {
	return sqrt((float)x * (float)x + (float)y * (float)y);
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline IntVector3 IntVector3::operator-() {
	x = -x;
	y = -y;
	z = -z;
}

inline IntVector3 operator+(const IntVector3 &p1, const IntVector3 &p2) {
	return IntVector3(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}
inline IntVector3 operator-(const IntVector3 &p1, const IntVector3 &p2) {
	return IntVector3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

inline IntVector3 IntVector3::operator+=(const IntVector3 &p) {
	return IntVector3(x + p.x, y + p.y, z + p.z);
}
inline IntVector3 IntVector3::operator-=(const IntVector3 &p) {
	return IntVector3(x - p.x, y - p.y, z - p.z);
}
inline IntVector3 IntVector3::operator+=(const int scalar) {
	return IntVector3(x + scalar, y + scalar, z + scalar);
}
inline IntVector3 IntVector3::operator-=(const int scalar) {
	return IntVector3(x - scalar, y - scalar, z - scalar);
}

inline IntVector3 operator+(const IntVector3 &p1, const int scalar) {
	return IntVector3(p1.x + scalar, p1.y + scalar, p1.z + scalar);
}
inline IntVector3 operator-(const IntVector3 &p1, const int scalar) {
	return IntVector3(p1.x - scalar, p1.y - scalar, p1.z - scalar);
}
inline IntVector3 operator+(const int scalar, const IntVector3 &p1) {
	return IntVector3(p1.x + scalar, p1.y + scalar, p1.z + scalar);
}
inline IntVector3 operator-(const int scalar, const IntVector3 &p1) {
	return IntVector3(p1.x - scalar, p1.y - scalar, p1.z - scalar);
}

inline IntVector3 operator*(const IntVector3& v1, const IntVector3& v2) {
	return IntVector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline IntVector3 operator*(const IntVector3& v, const int scalar) {
	return IntVector3(v.x * scalar, v.y * scalar, v.z * scalar);
}
inline IntVector3 operator*(const int scalar, const IntVector3& v) {
	return IntVector3(v.x * scalar, v.y * scalar, v.z * scalar);
}
inline IntVector3 operator/(const IntVector3& v, const float scalar) {
	if (scalar == 0.f) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a IntVector3 by zero", SEVERITY_FATAL);
		return IntVector3(0, 0, 0);
	}
	else
		return IntVector3((int)(v.x / scalar), (int)(v.y / scalar), (int)(v.z / scalar));
}

inline IntVector3 IntVector3::operator*=(const IntVector3& other) {
	return IntVector3(x * other.x, y * other.y, z * other.z);
}
inline IntVector3 IntVector3::operator*=(const int scalar) {
	return IntVector3(x * scalar, y * scalar, z * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool IntVector3::operator<(const IntVector3 &other) const {
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
inline bool IntVector3::operator>(const IntVector3 &other) const {
	return !(*this < other);
}
inline bool IntVector3::operator<=(const IntVector3 &other) const {
	if (x <= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool IntVector3::operator>=(const IntVector3 &other) const {
	if (x >= other.x) {
		return true;
	}
	else {
		return false;
	}
}
inline bool IntVector3::operator==(const IntVector3 &other) const {
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}
inline bool IntVector3::operator!=(const IntVector3 &other) const {
	return !(*this == other);
}