#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector2.hpp"

class AABB2 {
public:
	AABB2() : mins(), maxs() {}
	AABB2(const Vector2& mins, const Vector2& maxs) {
		this->mins = mins;
		this->maxs = maxs;
	}

	INLINE bool operator==(const AABB2& other) const;
	INLINE bool operator!=(const AABB2& other) const;

	Vector2 mins;
	Vector2 maxs;
};

class AABB2Int {
public:
	AABB2Int() : mins(), maxs() {}
	AABB2Int(const IntVector2& mins, const IntVector2& maxs) {
		this->mins = mins;
		this->maxs = maxs;
	}

	IntVector2 mins;
	IntVector2 maxs;
};

//---------------------------------------------------------------------------------------------------------------------------
//INLINE
//---------------------------------------------------------------------------------------------------------------------------
inline bool AABB2::operator==(const AABB2& other) const {
	return (mins == other.mins && maxs == other.maxs);
}
inline bool AABB2::operator!=(const AABB2& other) const {
	return (!(*this == other));
}