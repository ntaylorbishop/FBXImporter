#pragma once

#ifdef WIN32
#define PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/AABB2.hpp"

const int NUM_KEYS = 256;

class InputSystem;
extern InputSystem* g_theInputSystem;

#define NUM_KEY_0 0x60
#define NUM_KEY_1 0x61
#define NUM_KEY_2 0x62
#define NUM_KEY_3 0x63
#define NUM_KEY_4 0x64
#define NUM_KEY_5 0x65
#define NUM_KEY_6 0x66
#define NUM_KEY_7 0x67
#define NUM_KEY_8 0x68
#define NUM_KEY_9 0x69


enum eMouseBtn {
	MOUSE_LEFT = 0,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

class InputSystem {
public:
	//STRUCTORS
	InputSystem();

	bool HasQuit();
	void Quitting(bool isNowQuitting);

	bool GetKey(unsigned char asKey);
	bool GetKeyDown(unsigned char asKey);
	void SetKeyDownStatus(unsigned char asKey, bool isNowDown);

	bool GetMouseBtn(eMouseBtn btn);
	bool GetMouseBtnDown(eMouseBtn btn);
	void SetMouseBtnDown(eMouseBtn btn, bool isDown);

	void SetMouseWheelDelta(short wheelDelta);
	bool GetMouseWheelUp();
	bool GetMouseWheelDown();
	IntVector2 GetRelativeCursorPosition();
	bool IsMouseWithinQuad(const AABB2& quad);

	void SetCursorPosition(ScreenCoords pos);
	ScreenCoords GetCursorPosition();
	void HideMouseCursor();
	void ShowMouseCursor();

	//ENGINE-ONLY
	void DisableInputToGame();
	void EnableInputToGame();

private:
	bool m_isKeyDown[NUM_KEYS];
	bool quit;
	bool m_rightMouseDown;
	bool m_leftMouseDown;
	bool m_middleMouseDown;

	int m_mouseWheelUpDelta;
	int m_mouseWheelDownDelta;

	bool m_isInputEnabledForGame;
};

//TODO: Fix GetKeyDown / GetMouseBtnDown to work with frame count instead of the janky way its set up now