#pragma once

#include <string>
#include <algorithm>
#include "Engine/General/Utils/FileUtils.hpp"
#include "Engine/General/Utils/ErrorWarningAssert.hpp"
#include "Engine/General/Input/InputSystem.hpp"


class TheLogger;
extern TheLogger* g_theLogger;

class TheLogger {
public:
	//STRUCTORS
	TheLogger();
	~TheLogger();

	//FORMATTING LOGGING
	void PrintShaderCompileErrorToOutput(std::string error, std::string fileNameOfShader);

	//OPENGL UPDATE BIND POINTS
	void UpdateLastBoundIBO(int iboID);
	void UpdateLastBoundVBO(int vboID);
	void UpdateLastBoundVAO(int vaoID);
	void UpdateLastBoundProgram(int programID);

	void PrintBindPointIDsToOutputWindow();

private:
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
private:
	std::string m_workingDirectory;

	//OPENGL CLIENT STATE TRACKING
	int m_lastBoundVBO;
	int m_lastBoundIBO;
	int m_lastBoundVAO;
	int m_lastBoundProgram;
};