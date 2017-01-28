#pragma once

#include <iostream>
#include <fstream>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Utils/FileUtils/IBinaryWriter.hpp"

class FileBinaryWriter : public IBinaryWriter {
public:
	FileBinaryWriter();

	bool Open(const String& filename, bool append = false);
	virtual size_t WriteBytes(void* src, size_t numBytes) override;
	void Close();

private:
	FILE* m_fileHandle;
};