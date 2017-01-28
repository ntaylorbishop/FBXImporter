#pragma once

#include "Engine/General/Utils/FileUtils/IBinaryReader.hpp"

class FileBinaryReader : public IBinaryReader {
public:
	FileBinaryReader();

	bool Open(const String& filename, bool append = false);
	virtual size_t ReadBytes(void* out, size_t numBytes) override;
	void Close();

private:
	FILE* m_fileHandle;

	uint fileIdx;
};