#include "Game/TheApp.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
TheApp* g_theApp = nullptr;

//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------

TheApp::TheApp(ScreenCoords screenDimensions)
	: m_screenDimensions(screenDimensions)
{ 
	m_middleOfScreen = screenDimensions / 2;
}
TheApp::~TheApp() { }

//WINDOW STUFF
//---------------------------------------------------------------------------------------------------------------------------
bool TheApp::HasFocus() {
	return m_windowInFocus;
}
void TheApp::OnGainedFocus() {
	m_windowInFocus = true;
}
void TheApp::OnLostFocus() {
	m_windowInFocus = false;
}
ScreenCoords TheApp::GetScreenDimensions() const {
	return m_screenDimensions;
}

IntVector2 TheApp::GetCursorDelta() {
	ScreenCoords cursorPos = g_theInputSystem->GetCursorPosition();
	g_theInputSystem->SetCursorPosition(m_middleOfScreen);
	m_cursorDelta = cursorPos - m_middleOfScreen;
	return m_cursorDelta;
}