#ifndef __GAMEPAD_H_INCLUDE__
#define __GAMEPAD_H_INCLUDE__

#include "../main/GameHeaders.h"

#define MAX_CONTROLLERS 4
namespace Input { 

	enum XButtons { 
		DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
		DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
		LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
		RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
		LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RIGHT_SHOULDER  = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A_BUTTON = XINPUT_GAMEPAD_A,
		B_BUTTON = XINPUT_GAMEPAD_B,
		X_BUTTON = XINPUT_GAMEPAD_X,
		Y_BUTTON = XINPUT_GAMEPAD_Y
	}; // XButtons

	class XGamePad {
	private:
		struct CONTROLLER_INFO {
			XINPUT_STATE curState;
			BOOLEAN isConnected; 
		};

		// Array for max controllers and a NULL controller
		CONTROLLER_INFO controllers[MAX_CONTROLLERS];
		CONTROLLER_INFO NULL_CONTROLLER;
	public:
		XGamePad();
		void GetControllerStates();
		BOOLEAN IsButtonPressedForController(int , int);
		CONTROLLER_INFO GetController(int);

	};
} // Input
#endif
/* eof */