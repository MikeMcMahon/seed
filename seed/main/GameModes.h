#ifndef __GAMEMODE_H_INCLUDE__
#define __GAMEMODE_H_INCLUDE__
#include "GameHeaders.h"

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
	BOOL ValidGameModeTransition(MODES, MODES); // Determins if the source gamemode can be transitioned into the next gamemode 
}; // GameModes
#endif
/* eof */