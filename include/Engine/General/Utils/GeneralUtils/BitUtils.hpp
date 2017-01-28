#pragma once

#include <bitset>
#include "Engine/General/Core/EngineCommon.hpp"

namespace BitUtils {
	inline void SetBit(BYTE& bitFlags, BYTE bitMask) {
		bitFlags |= bitMask;
		bitFlags = bitFlags | bitMask;
	}
	inline void SetBit(int& bitFlags, int bitMask) {
		bitFlags |= bitMask;
		bitFlags = bitFlags | bitMask;
	}

	inline bool IsBitSet(BYTE bitFlags, BYTE bitMask) {
		return (bitFlags & bitMask) != 0;
	}
	inline bool IsBitSet(int bitFlags, int bitMask) {
		return (bitFlags & bitMask) != 0;
	}

	inline void ClearBit(BYTE& bitFlags, BYTE bitMask) {
		bitFlags &= ~bitMask;
	}
	inline void ClearBit(int& bitFlags, int bitMask) {
		bitFlags &= ~bitMask;
	}

	String GetBitsAsString(BYTE bitsToOutput);
	String GetBitsAsString(int bitsToOutput);
}