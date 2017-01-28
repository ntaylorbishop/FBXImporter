#pragma once
#include "Engine/General/Utils/GeneralUtils/Endianness.hpp"
#include "Engine/Math/Matrix4.hpp"

class IBinaryWriter {
public:
	virtual size_t WriteBytes(void* src, size_t numBytes) = 0;

	void SetEndianness(eEndianness newEnd);
	void ByteSwap(void* data, size_t dataSize);
	bool WriteString(const String& str);

	bool WriteChar(char data);
	bool WriteInt(int data);
	bool WriteUnsignedInt(uint data);
	bool WriteByte(BYTE data);
	bool WriteFloat(float data);
	bool WriteDouble(double data);
	bool WriteMatrix(const Matrix4& matrix);

	//Write functions
	template <typename T>
	bool Write(const T& v) {
		T copy = v;
		if (GetLocalEndianness() != m_endianness) {
			ByteSwap(&copy, sizeof(T));
		}
		return WriteBytes(&copy, sizeof(T)) == sizeof(T);
	}

private:
	eEndianness m_endianness = LITTLE_ENDIAN;
};