#pragma once

#include "Engine/Math/AABB2.hpp"

class UIComponent {
public:
	UIComponent();

	virtual void Update(float deltaSeconds) = 0;
	virtual void Render() = 0;

private:
	AABB2Int rect;
};