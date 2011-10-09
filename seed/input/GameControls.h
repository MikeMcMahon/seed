#pragma once

namespace Input { 
	struct GameControls { enum Buttons { 
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_START,
		KEY_PAUSE = KEY_START,
		KEY_BACK,
		KEY_SELECT = KEY_BACK,
		KEY_INTERACT,
		KEY_RUN,
		KEY_CANCEL
	};};
}