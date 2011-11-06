#pragma once

#include "../input/GameControls.h"
#include "../sprites/GameSprite.h"
#include "../gui/StartMenu.h"
#include "../input/XGamePad.h"

#include "../main/GameModes.h"

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
namespace Game { 
    class DarkSeed
    {
    private:
		
	    Sprites::GameSprite gameSprites[MAX_SPRITES];
        GameModes::modes gameMode;

    public:
   
    #ifdef RENDER_ENG_DX
        RENDER lpfRender;
        UPDATE lpfUpdateSc;
        MOVE lpfMoveSprts;
        LOADTX lpfLoadTxtrs;
    #else
        // If we support GL or DX...we don't support GL yet and probably not for a while
    #endif

        WindowOffsets* windowOffsets;
        RenderEngine::type engineType;         // The kind of engine to render against, DX only right now

	    DarkSeed(void);
	    ~DarkSeed(void);
	    void InitGame();
	    void MoveSprites(float interpolation);
        void UpdateSprites();
        void Render();
        void UpdateScene();

    private:
        void LoadTextures();
    }; // DarkSeed
}
/* eof */