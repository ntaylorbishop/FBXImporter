#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/General/Console/Command.hpp"
#include "Engine/Math.hpp"

class TheApp;
extern TheApp* g_theApp;

class TheApp {
public:
	//STRUCTORS
	TheApp(ScreenCoords screenDimensions);
	~TheApp();

	//WINDOW STUFF
	bool HasFocus();
	void OnGainedFocus();
	void OnLostFocus();
	ScreenCoords GetScreenDimensions() const;

	IntVector2 GetCursorDelta();

private:
	//WINDOW STUFF
	ScreenCoords m_middleOfScreen;
	ScreenCoords m_cursorDelta;
	ScreenCoords m_screenDimensions;
	bool m_windowInFocus;
};