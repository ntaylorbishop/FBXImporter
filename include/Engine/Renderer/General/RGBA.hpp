#pragma once

#include "Engine/General/Utils/StringUtils.hpp"

class RGBA {
public:
	RGBA();

	//Normalized RGBA values
	RGBA(float r, float g, float b, float a);

	//RGBA values in hex
	RGBA(int r, int g, int b, int a);
	RGBA(int r, int g, int b, float a);

	//Normalizes this color's RGBA's to the given hex values
	void ConvertHex(int r, int g, int b, int a);
	void ConvertHex(int r, int g, int b);

	String ToString() const { return std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(a); }

public:
	float r;
	float g;
	float b;
	float a;

public:
	static const RGBA WHITE;
	static const RGBA BLACK;
	static const RGBA RED;
	static const RGBA GREEN;
	static const RGBA BLUE;
	static const RGBA YELLOW;
	static const RGBA MAGENTA;
	static const RGBA CYAN;
	static const RGBA GREY;
	static const RGBA ORANGE;
};