#pragma once

#include "Engine/General/Core/Window.hpp"

class WindowHandler;
extern WindowHandler* g_theWindowHandler;

class WindowHandler {
public:
	WindowHandler();

	bool RegisterMainWindow(HWND mainWindow);
	bool RegisterWindow(HWND newWindow, String name);

	Window GetMainWindow();
	Window GetWindowByName(String name);

private:
	Window m_mainWindow;

	std::vector<Window> m_registeredWindows;
};