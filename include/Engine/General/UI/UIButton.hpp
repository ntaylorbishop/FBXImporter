#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/General/RGBA.hpp"

class UIButton {
public:
	//STRUCTORS
	UIButton();
	UIButton(uint rectLeft, uint rectRight, uint rectBottom, uint rectTop, RGBA inCol, RGBA outCol);

	//GETTERS
	bool IsPositionInRect(IntVector2 position) const;
	bool HasBeenClickedOnThisFrame() const;

public:
	uint left;
	uint right;
	uint top;
	uint bottom;

	RGBA inColor;
	RGBA outColor;
};