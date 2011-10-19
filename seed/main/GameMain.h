#pragma once

#include "..\input\GameControls.h"
#include "..\sprites\GameSprite.h"
#include "..\gui\StartMenu.h"
#include "..\input\XGamePad.h"

#include "GameModes.h"
#ifdef RENDER_ENG_DX 
typedef void (*RENDER)(Sprites::GameSprite*, int);
typedef void (*UPDATE)(Sprites::GameSprite*);
typedef void (*MOVE)(Sprites::GameSprite*, float);
typedef void (*LOADTX)(Sprites::GameSprite*);
#else
// Typedef's for opengl when we support it
#endif

struct RenderEngine { enum type { 
    directx,
	opengl};};

class GameMain
{
private:
	Sprites::GameSprite gameSprites[MAX_SPRITES];
    GameModes::modes gameMode;

public:
// If we support GL or DX...we don't support GL yet and probably not for a while
#ifdef RENDER_ENG_DX
    RENDER lpfRender;
    UPDATE lpfUpdateSc;
    MOVE lpfMoveSprts;
    LOADTX lpfLoadTxtrs;
#else
#endif

    WindowOffsets* windowOffsets;

    RenderEngine::type engineType;         // The kind of engine to render against, DX only right now

	GameMain(void)
	{
        // We only support directx right now
#ifdef RENDER_ENG_DX
        this->engineType = RenderEngine::directx;
#else
		this->engineType = RenderEngine::opengl;
#endif
	}

	~GameMain(void)
	{
	}

	/************************************************
	** InitGame()
	** Initializes the game
	**	Creates the StartMenu To Display
	**	Pre-Loads any textures / resources
	*************************************************/
	void InitGame() { 
		gameMode = GameModes::MAIN_MENU;
		
        // HACK - Demo sprite to test sprite engine
		Sprites::GameSprite *gs = new Sprites::GameSprite(L"", L"", WINDOW_WIDTH, WINDOW_HEIGHT);
		gs[0].sprite.isVisible = true;
		gs[0].sprite.textureLoaded = false;
		gs[0].sprite.canAnimate = true;
		gs[0].sprite.canMove = false;
		gs[0].sprite.position.z = 0.5f;
	    this->gameSprites[0] = *gs; 
		this->LoadTextures();

	}


	/************************************************
	** MoveSprites()
	**	Handles any incomming key presses
	*************************************************/
	void MoveSprites(float interpolation) { 
        // Calculate the window offsets based on the current map sprite
        // TODO - there will be times when we don't need to calculate offsets (waste of time) probably want to create a flag 
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

