#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h> // include the Xinput API
#include <stdio.h>
#pragma comment( lib, "xinput9_1_0" ) // Link in the xinput.lib static library // #Eiserloh: Explicitly use XInput v9_1_0, since v1_4 is not supported under Windows 7

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/PolarCoords.hpp"
#include "Engine/Math/MathUtils.hpp"

enum eXboxBtn {
	XB_DPAD_UP = 0,
	XB_DPAD_DOWN,
	XB_DPAD_LEFT,
	XB_DPAD_RIGHT,
	XB_START,
	XB_BACK,
	XB_LEFT_THUMB,
	XB_RIGHT_THUMB,
	XB_RB,
	XB_LB,
	XB_A,
	XB_B,
	XB_X,
	XB_Y
};

class XboxController {
public:
	XboxController();
	XboxController(int controllerNumber); //A new XboxController should be instantiated for each controller you wish to use
	void Update();
	void updateLeftStick();
	void updateRightStick();

	bool getButton(eXboxBtn btn) const;
	bool getButtonDown(eXboxBtn btn) const;

	PolarCoords getLeftStickPositionPolar(); //Returns radius and angle
	PolarCoords getRightStickPositionPolar(); //Returns radius and angle
	Vector2 getLeftStickPosition();
	Vector2 getRightStickPosition();
	float getLeftTriggerValue() const; //Returns value between 0 and 1
	float getRightTriggerValue() const; //Returns value between 0 and 1

	bool isConnected();
private:
	int controllerNumber;
	WORD buttons;
	WORD prevButtons;
	int button_frameNumber[14];
	Vector2 lThumb; //The actual stick position
	Vector2 rThumb; //The actual stick position
	PolarCoords lThumbPolar;
	PolarCoords rThumbPolar;

	int leftTrigger;
	int rightTrigger;
	bool connected;

	int frameNumber;
};

// XINPUT_GAMEPAD_DPAD_UP	    0x0001 0000 0000 0000 0001
// XINPUT_GAMEPAD_DPAD_DOWN	    0x0002 0000 0000 0000 0010
//XINPUT_GAMEPAD_DPAD_LEFT	    0x0004 0000 0000 0000 0100
//XINPUT_GAMEPAD_DPAD_RIGHT	    0x0008 0000 0000 0000 1000
//XINPUT_GAMEPAD_START	        0x0010 0000 0000 0001 0000
//XINPUT_GAMEPAD_BACK	        0x0020 0000 0000 0010 0000
//XINPUT_GAMEPAD_LEFT_THUMB	    0x0040 0000 0000 0100 0000
//XINPUT_GAMEPAD_RIGHT_THUMB	0x0080 0000 0000 1000 0000
//XINPUT_GAMEPAD_LEFT_SHOULDER	0x0100 0000 0001 0000 0000
//XINPUT_GAMEPAD_RIGHT_SHOULDER	0x0200 0000 0010 0000 0000
//XINPUT_GAMEPAD_A	            0x1000 0000 0100 0000 0000
//XINPUT_GAMEPAD_B	            0x2000 0000 1000 0000 0000
//XINPUT_GAMEPAD_X	            0x4000 0001 0000 0000 0000
//XINPUT_GAMEPAD_Y	            0x8000 0010 0000 0000 0000