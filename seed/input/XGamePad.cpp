#include "XGamePad.h"

Input::XGamePad::XGamePad() { 
	// By default this is disconnected
	NULL_CONTROLLER.isConnected = false;
	ZeroMemory(&controllers, MAX_CONTROLLERS * sizeof(CONTROLLER_INFO));	// Zero this out - remove that gobldygook 
} // XGamePad

BOOLEAN Input::XGamePad::IsButtonPressedForController(int controller, int button) {
	GetController(controller);
	if (GetController(controller).isConnected) { 
		if ((GetController(controller).curState.Gamepad.wButtons & button))
			return TRUE;
		else
			return FALSE;
	}

	// Can't get the button from an inactive controller
	return FALSE;
} // IsButtonPressedForController

Input::XGamePad::CONTROLLER_INFO Input::XGamePad::GetController(int controller) { 
	if (controller < MAX_CONTROLLERS) {
		return controllers[controller];
	}
	
	// Return a null controller
	return XGamePad::NULL_CONTROLLER;
} // GetController


void Input::XGamePad::GetControllerStates() { 
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++) {
		
		ZeroMemory(&controllers[i].curState, sizeof(XINPUT_STATE));
		
		// Get the state
		DWORD dwResult = XInputGetState(i, &controllers[i].curState);
		controllers[i].isConnected = (dwResult == ERROR_SUCCESS);
	}
} // GetControllerStates

/* eof */