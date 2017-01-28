#pragma once

#include "Engine/General/Core/EngineCommon.hpp"

enum eEndianness {
	LITTLE_ENDIAN = 0,
	BIG_ENDIAN
};

eEndianness GetLocalEndianness();