#pragma once

#include <vector>
#include <string>
#include "Engine/General/Utils/StringUtils.hpp"
#include "Engine/Renderer/General/RGBA.hpp"

class Command {
public:
	//STRUCTORS
	Command(std::string commandString);
	Command(std::vector<std::string> commandString);
	~Command();

	std::string GetCommandName() const;
	bool GetNextInt(int& out);
	bool GetNextString(std::string& out);
	bool GetNextColor(RGBA& out);
	bool GetNextFloat(float& out);

private:
	std::vector<std::string> m_stringTokens;
	int m_currIdx;
};