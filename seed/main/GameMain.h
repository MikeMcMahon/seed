#pragma once

#include "..\input\GameControls.h"
#include "..\sprites\GameSprite.h"
#include "..\gui\StartMenu.h"
#include "..\input\XGamePad.h"

#include "GameModes.h"

typedef void (*RENDER_DX)(Sprites::GameSprite*, int);
typedef void (*UPDATE_DX)(Sprites::GameSprite*);
typedef void (*MOVE_DX)(Sprites::GameSprite*, float);
typedef void (*LOADTX_DX)(Sprites::GameSprite*);

struct RenderEngine { enum type { 
    directx };};

class GameMain
{
private:
	Sprites::GameSprite gameSprites[MAX_SPRITES];
    GameModes::modes gameMode;

public:
// If we support GL or DX...we don't support GL yet and probably not for a while...ever 
    RENDER_DX lpfRender;
    UPDATE_DX lpfUpdateSc;
    MOVE_DX lpfMoveSprts;
    LOADTX_DX lpfLoadTxtrs;

    WindowOffsets* windowOffsets;

    RenderEngine::type engineType;         // The kind of engine to render against, DX only right now

	GameMain(void)
	{
        // We only support directx right now
        this->engineType = RenderEngine::directx;
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
	** MoveSprites()
	**	Handles any incomming key presses
	*************************************************/
	void MoveSprites(float interpolation) { 
        // Calculate the window offsets based on the current map sprite
        // TODO - there will be times when we don't need to calculate offsets (waste of time) probably want to create a flag 
        this->windowOffsets->offsetBottom = 100; // testing
        (*this->lpfMoveSprts)(gameSprites, interpolation);
	} // MoveSprites

    /**************************************
    *** Handles incrementing the animation frame 
    *** Sprites must maintain their own knowledge of FPS 
    *** TODO - sprites should animate on time without having to calculate skips themselves
    ***************************************/
    void UpdateSprites() { 
	    for (int i = 0; i < MAX_SPRITES; i++) { 
		    if (gameSprites[i].sprite.isVisible && gameSprites[i].sprite.canAnimate) { 
			    gameSprites[i].incrementFrame();

			    // reset the frames if we're past the max # of frames
			    if (gameSprites[i].curFrame() >= gameSprites[i].sprite.animation.numFrames) { 
				    gameSprites[i].curFrame(0);
			    }
		    }
	    }
    } // UpdateSprites

	/************************************************
	** Render()
	**	Calls the render function passed in 
	** Returns
	*************************************************/
    void Render() { 
        (*this->lpfRender)(this->gameSprites, 0);
    }

	/************************************************
	** UpdateScene()
	**	Calls the updatescene function 
	*************************************************/
    void UpdateScene() { 
        (*this->lpfUpdateSc)(this->gameSprites);
    }

private:
    void LoadTextures() { 
        // Sprites to load textures for
        (*this->lpfLoadTxtrs)(this->gameSprites);
    }
};

