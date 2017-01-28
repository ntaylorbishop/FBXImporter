#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#include <vector>
#include <string>
#include "io.h"

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Utils/StringUtils.hpp"

namespace FileUtils {
	bool LoadBinaryFileToBuffer(const std::string& filePath, std::vector<unsigned char>& out_buffer);
	bool SaveBufferToBinaryFile(const std::string& filePath, const std::vector<unsigned char>& buffer);

	std::vector<String> GetAllFilenamesInDirectory(const String& relDir);

	bool DoesFileExist(const String& filename);

	//TODO: Create logging stuff
	//bool LogMessage(const std::string& message);
	//bool LogMessage(const std::vector<unsigned char>& message);
}