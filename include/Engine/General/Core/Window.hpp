#pragma once

#include "Engine/General/Input/InputSystem.hpp"

class Window {
public:
	//STRUCTORS
	Window();
	Window(HWND window, String name);

	//GETTERS
	String GetName();
	IntVector2 GetWindowOffset();
	IntVector2 GetRelativeMousePosition();
	bool MouseIsInWindow();

	static IntVector2 GetDesktopResolution();

private:
	//PRIVATE MEMBER FUNCTIONS
	IntVector2 GetWindowSize();

private:
	HWND m_window;
	String m_name;
	IntVector2 m_windowSize;
};