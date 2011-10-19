#include "GameMain.h"

using namespace Seed;

GameMain::GameMain(void)
{
    // We only support directx right now
#ifdef RENDER_ENG_DX
    this->engineType = RenderEngine::directx;
#else
	this->engineType = RenderEngine::opengl;
#endif
}

GameMain::~GameMain(void)
{
}

/************************************************
** InitGame()
** Initializes the game
**	Creates the StartMenu To Display
**	Pre-Loads any textures / resources
*************************************************/
void GameMain::InitGame() { 
	gameMode = GameModes::MAIN_MENU;
		
    // HACK - Demo sprite to test sprite engine
	Sprites::GameSprite *gs = new Sprites::GameSprite(L"../textures/ball-bounce-512x64.png", L"bouncingball", 64, 64);
	gs[0].IsVisible ( true );
    gs[0].CanAnimate ( true );
    gs[0].CanMove ( true );
    gs[0].AnimationDetail(8.0f, 8);
	gs[0].Position ( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.5f );
    gs[0].kindOf = Sprites::Type::background;
        
    Sprites::GameSprite *gs2 = new Sprites::GameSprite(L"../textures/main-menu-1024x768.png", L"background", WINDOW_WIDTH, WINDOW_HEIGHT);
    gs2->IsVisible(true);
    gs2->Position(0, 0, 0.5f );
    gs2->kindOf = Sprites::Type::background;

    this->gameSprites[0] = *gs2;
	this->gameSprites[1] = *gs; 
	this->LoadTextures();

} // InitGame


/************************************************
** MoveSprites()
**	Handles any incomming key presses
*************************************************/
void GameMain::MoveSprites(float interpolation) { 
    // Calculate the window offsets based on the current map sprite
    // TODO - there will be times when we don't need to calculate offsets (waste of time) probably want to create a flag 
    (*this->lpfMoveSprts)(gameSprites, interpolation);
} // MoveSprites

/**************************************
*** Handles incrementing the animation frame 
*** Sprites must maintain their own knowledge of FPS 
*** TODO - sprites should animate on time without having to calculate skips themselves
***************************************/
void GameMain::UpdateSprites() { 
	for (int i = 0; i < MAX_SPRITES; i++) { 
        if (gameSprites[i].IsVisible() && gameSprites[i].CanAnimate()) { 
			gameSprites[i].IncrementFrame();
		}
	}
} // UpdateSprites

/************************************************
** Render()
**	Calls the render function passed in 
** Returns
*************************************************/
void GameMain::Render() { 
    (*this->lpfRender)(this->gameSprites, 0);
}

/************************************************
** UpdateScene()
**	Calls the updatescene function 
*************************************************/
void GameMain::UpdateScene() { 
    (*this->lpfUpdateSc)(this->gameSprites);
}

void GameMain::LoadTextures() { 
    // Sprites to load textures for
    (*this->lpfLoadTxtrs)(this->gameSprites);
}