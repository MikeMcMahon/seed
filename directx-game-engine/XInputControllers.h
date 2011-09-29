#include "GameHeaders.h"

#define MAX_CONTROLLERS 1

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
};
class XControllers {
	// Basic controller structure
	struct CONTROLLER_INFO {
		XINPUT_STATE curState;
		BOOLEAN isConnected; 
	};

	// Array for max controllers and a NULL controller
	CONTROLLER_INFO controllers[MAX_CONTROLLERS];
	CONTROLLER_INFO NULL_CONTROLLER;
public:
	XControllers();
	void GetControllerStates();
	BOOLEAN IsButtonPressedForController(int , int);
	CONTROLLER_INFO GetController(int);

};


XControllers::XControllers() { 
	// By default this is disconnected
	NULL_CONTROLLER.isConnected = false;
}

BOOLEAN XControllers::IsButtonPressedForController(int controller, int button) {
	GetController(controller);
	if (GetController(controller).isConnected) { 
		if ((GetController(controller).curState.Gamepad.wButtons & button))
			return TRUE;
		else
			return FALSE;
	}

	// Can't get the button from an inactive controller
	return FALSE;
}

XControllers::CONTROLLER_INFO XControllers::GetController(int controller) { 
	if (controller < MAX_CONTROLLERS) {
		return controllers[controller];
	}
	
	// Return a null controller
	return XControllers::NULL_CONTROLLER;
}


void XControllers::GetControllerStates() { 
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++) {
		
		ZeroMemory(&controllers[i].curState, sizeof(XINPUT_STATE));
		
		// Get the state
		DWORD dwResult = XInputGetState(i, &controllers[i].curState);
		controllers[i].isConnected = (dwResult == ERROR_SUCCESS);
	}
}
