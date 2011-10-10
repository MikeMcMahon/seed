#pragma once

class GameModes { 
public:
	static enum MODES { 
		MAIN_MENU,
		IN_GAME,
		PAUSE,
		GAME_OVER,
		LOADING_SCREEN,
		CREDITS
	};
	bool ValidGameModeTransition(MODES, MODES); // Determins if the source gamemode can be transitioned into the next gamemode 
}; // GameModes

/* eof */