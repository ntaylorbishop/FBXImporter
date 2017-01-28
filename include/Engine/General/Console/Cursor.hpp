#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"

class Cursor {
public:
	//STRUCTORS
	Cursor(float height, float thickness, float blinkSpeed, Vector2 startingPos);
	~Cursor();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void BlinkCursor() const;

	void MoveCursor(float amount);
	void ResetCursorPosition();

	//GETTERS SETTERS
	Vector2 GetStartingPosition();
	float GetHeight();

private:
	Vector2 m_position;
	float m_age;
	float m_height;
	float m_thickness;
	float m_blinkSpeed;

	float m_timeAlive;
	Vector2 m_startingPosition;
	bool m_tickingDown;
};