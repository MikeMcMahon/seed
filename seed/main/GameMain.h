#pragma once

#include "..\input\GameControls.h"
#include "..\sprites\GameSprite.h"
#include "..\gui\StartMenu.h"

#include "GameModes.h"

class GameMain
{
private:
	Sprites::GameSprite gameSprites[MAX_SPRITES];
	GameModes::modes gameMode;

public:

	GameMain(void)
	{
	}

	~GameMain(void)
	{
	}

	/************************************************
	** InitGame()
	** Initializes the game
	**	Creates the StartMenu To Display
	**	Pre-Loads any textures / resources
	** Returns
	**	an array of game sprites to be rendered by the system.
	*************************************************/
	Sprites::GameSprite* InitGame() { 
		gameMode = GameModes::MAIN_MENU;

		// Get the main menu
		
		return gameSprites;
	}


	/************************************************
	** HandleControlPress()
	**	Handles any incomming key presses
	** Returns
	**	If this returns true then the caller needs to
	**	ensure they re-request the sprites from the system 
	**  If this is false then the key resulted in no actions that require updating the sprites
	*************************************************/
	Sprites::GameSprite* MoveSprites(float interpolation) { 


		return gameSprites;
	}

};

