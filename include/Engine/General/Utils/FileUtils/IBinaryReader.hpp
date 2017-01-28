#pragma once
#include "Engine/General/Utils/GeneralUtils/Endianness.hpp"
#include "Engine/Math/Matrix4.hpp"

class IBinaryReader {
public:
	virtual size_t ReadBytes(void* out, size_t numBytes) = 0;

	template <typename T>
	bool Read(T* out) {
		T* copy = out;
		if (GetLocalEndianness() != m_endianness) {
			ByteSwap(&copy, sizeof(T));
		}
		return ReadBytes(copy, sizeof(T)) == sizeof(T);
	}

	bool ReadChar(char* out);
	bool ReadInt(int* out);
	bool ReadUnsignedInt(uint* out);
	bool ReadByte(BYTE* out);
	bool ReadFloat(float* out);
	bool ReadDouble(double* out);
	bool ReadMatrix(Matrix4* out);
	bool ReadString(String* out);

	void ByteSwap(void* data, size_t dataSize);

private:
	eEndianness m_endianness = LITTLE_ENDIAN;

	uint m_currByteIdx;
};