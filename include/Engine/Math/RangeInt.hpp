#pragma once

#include "Engine/Math/MathUtils.hpp"

class RangeInt {
public:
	//STRUCTORS
	RangeInt();
	RangeInt(int min, int max);

	//GETTERS SETTERS
	int GetMin() const { return m_min; }
	int GetMax() const { return m_max; }
	String ToString() const { return std::to_string(m_min) + "," + std::to_string(m_max); }

	//ROLL
	int Roll();

	//OPERATOR OVERLOADS
	INLINE bool operator==(const RangeInt& other);

private:
	int m_min;
	int m_max;
};

//---------------------------------------------------------------------------------------------------------------------------
//INLINE
//---------------------------------------------------------------------------------------------------------------------------
inline bool RangeInt::operator==(const RangeInt& other) {
	return (m_min == other.GetMin() && m_max == other.GetMax());
}