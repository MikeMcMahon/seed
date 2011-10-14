#include "GameModes.h"
bool GameModes::ValidGameModeTransition(GameModes::modes srcMode, GameModes::modes destMode) { 
	switch(srcMode) { 
	case this->LOADING_SCREEN:
		return true;	// Loading screen go anywhere! 
	case this->MAIN_MENU:
		// Game modes we can land on from the main menu
		switch(destMode) { 
		case this->IN_GAME:
		case this->CREDITS:
		case this->LOADING_SCREEN:
			return true;
		default:
			return false;
		}
		break;
	case this->CREDITS:
		switch(destMode) { 
		case this->MAIN_MENU:
		case this->LOADING_SCREEN:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
} // ValidGameModeTransition

/* eof */