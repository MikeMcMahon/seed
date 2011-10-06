#include "GameModes.h"
BOOL GameModes::ValidGameModeTransition(GameModes::MODES srcMode, GameModes::MODES destMode) { 
	switch(srcMode) { 
	case this->LOADING_SCREEN:
		return TRUE;	// Loading screen go anywhere! 
	case this->MAIN_MENU:
		// Game modes we can land on from the main menu
		switch(destMode) { 
		case this->IN_GAME:
		case this->CREDITS:
		case this->LOADING_SCREEN:
			return TRUE;
		default:
			return FALSE;
		}
		break;
	case this->CREDITS:
		switch(destMode) { 
		case this->MAIN_MENU:
		case this->LOADING_SCREEN:
			return TRUE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
} // ValidGameModeTransition

/* eof */