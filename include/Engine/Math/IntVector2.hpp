#pragma once
#include <math.h>
#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

class Vector2;

typedef IntVector2 ScreenCoords;

class IntVector2 {
public:
	IntVector2();
	IntVector2(int x, int y);
	IntVector2(const IntVector2& other);

	Vector2 ToVector2() const;
	String ToString() const;

	float Length() const;

	//OPERATOR OVERLOADS
	IntVector2 operator-();

	friend IntVector2 operator+(const IntVector2 &p1, const IntVector2 &p2);
	friend IntVector2 operator-(const IntVector2 &p1, const IntVector2 &p2);

	friend IntVector2 operator+(const IntVector2 &p1, const int scalar);
	friend IntVector2 operator-(const IntVector2 &p1, const int scalar);
	friend IntVector2 operator+(const int scalar, const IntVector2 &p1);
	friend IntVector2 operator-(const int scalar, const IntVector2 &p1);

	IntVector2 operator+=(const IntVector2 &p);
	IntVector2 operator-=(const IntVector2 &p);
	IntVector2 operator+=(const int scalar);
	IntVector2 operator-=(const int scalar);


	friend IntVector2 operator*(const IntVector2& v1, const IntVector2& v2);
	friend IntVector2 operator*(const IntVector2& v, const int scalar);
	friend IntVector2 operator*(const int scalar, const IntVector2& v);
	friend IntVector2 operator/(const IntVector2& v, const int scalar);

	IntVector2 operator*=(const IntVector2& other);
	IntVector2 operator*=(const int scalar);

	//CONDITIONAL OPERATORS
	bool operator<(const IntVector2 &other) const;
	bool operator>(const IntVector2 &other) const;
	bool operator<=(const IntVector2 &other) const;
	bool operator>=(const IntVector2 &other) const;
	bool operator==(const IntVector2 &other) const;
	bool operator!=(const IntVector2 &other) const;

public:
	int x;
	int y;
};

//-----------------------------------------------------------------------------------------------------------------------------------------
//INLINE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline float IntVector2::Length() const {
	return sqrt((float)x * (float)x + (float)y * (float)y);
}

//OPERATOR OVERLOADS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline IntVector2 IntVector2::operator-() {
	x = -x;
	y = -y;
}

inline IntVector2 operator+(const IntVector2 &p1, const IntVector2 &p2) {
	return IntVector2(p1.x + p2.x, p1.y + p2.y);
}
inline IntVector2 operator-(const IntVector2 &p1, const IntVector2 &p2) {
	return IntVector2(p1.x - p2.x, p1.y - p2.y);
}

inline IntVector2 IntVector2::operator+=(const IntVector2 &p) {
	return IntVector2(x + p.x, y + p.y);
}
inline IntVector2 IntVector2::operator-=(const IntVector2 &p) {
	return IntVector2(x - p.x, y - p.y);
}
inline IntVector2 IntVector2::operator+=(const int scalar) {
	return IntVector2(x + scalar, y + scalar);
}
inline IntVector2 IntVector2::operator-=(const int scalar) {
	return IntVector2(x - scalar, y - scalar);
}

inline IntVector2 operator+(const IntVector2 &p1, const int scalar) {
	return IntVector2(p1.x + scalar, p1.y + scalar);
}
inline IntVector2 operator-(const IntVector2 &p1, const int scalar) {
	return IntVector2(p1.x - scalar, p1.y - scalar);
}
inline IntVector2 operator+(const int scalar, const IntVector2 &p1) {
	return IntVector2(p1.x + scalar, p1.y + scalar);
}
inline IntVector2 operator-(const int scalar, const IntVector2 &p1) {
	return IntVector2(p1.x - scalar, p1.y - scalar);
}

inline IntVector2 operator*(const IntVector2& v1, const IntVector2& v2) {
	return IntVector2(v1.x * v2.x, v1.y * v2.y);
}
inline IntVector2 operator*(const IntVector2& v, const int scalar) {
	return IntVector2(v.x * scalar, v.y * scalar);
}
inline IntVector2 operator*(const int scalar, const IntVector2& v) {
	return IntVector2(v.x * scalar, v.y * scalar);
}
inline IntVector2 operator/(const IntVector2& v, const int scalar) {
	if (scalar == 0.f) {
		SystemDialogue_Okay("Divide by Zero", "Attempted to divide a IntVector2 by zero", SEVERITY_FATAL);
		return IntVector2(0, 0);
	}
	else
		return IntVector2(v.x / scalar, v.y / scalar);
}

inline IntVector2 IntVector2::operator*=(const IntVector2& other) {
	return IntVector2(x * other.x, y * other.y);
}
inline IntVector2 IntVector2::operator*=(const int scalar) {
	return IntVector2(x * scalar, y * scalar);
}

//CONDITIONAL OPERATORS
//-----------------------------------------------------------------------------------------------------------------------------------------
inline bool IntVector2::operator<(const IntVector2 &other) const {
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
		else if (y >= other.y) {
			return false;
		}
	}
	return false;
}
inline bool IntVector2::operator>(const IntVector2 &other) const {
	return !(*this < other);
}
inline bool IntVector2::operator<=(const IntVector2 &other) const {
	if (x <= other.x)
		return true;
	else
		return false;
}
inline bool IntVector2::operator>=(const IntVector2 &other) const {
	if (x >= other.x)
		return true;
	else
		return false;
}
inline bool IntVector2::operator==(const IntVector2 &other) const {
	if (x == other.x && y == other.y)
		return true;
	else
		return false;
}
inline bool IntVector2::operator!=(const IntVector2 &other) const {
	return !(*this == other);
}