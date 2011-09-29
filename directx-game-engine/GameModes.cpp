#include "GameModes.h"
BOOL GameModes::ValidGameModeTransition(GameModes::MODES srcMode, GameModes::MODES destMode) { 
	switch(srcMode) { 
	case MODES::LOADING_SCREEN:
		return TRUE;	// Loading screen go anywhere! 
	case MODES::MAIN_MENU:
		// Game modes we can land on from the main menu
		switch(destMode) { 
		case MODES::IN_GAME:
		case MODES::CREDITS:
		case MODES::LOADING_SCREEN:
			return TRUE;
		default:
			return FALSE;
		}
		break;
	case MODES::CREDITS:
		switch(destMode) { 
		case MODES::MAIN_MENU:
		case MODES::LOADING_SCREEN:
			return TRUE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
}