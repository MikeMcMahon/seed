#pragma once

#include "GameControls.h"

#define MAX_CONTROLLERS 4
namespace Input { 

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
/* eof */