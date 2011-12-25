#include "DarkSeed.h"

using namespace Game;

DarkSeed::DarkSeed(void)
{
    // We only support directx right now
#ifdef RENDER_ENG_DX
    this->engineType = RenderEngine::directx;
#else
	this->engineType = RenderEngine::opengl;
#endif
}

DarkSeed::~DarkSeed(void)
{
}

/************************************************
** InitGame()
** Initializes the game
**	Creates the StartMenu To Display
**	Pre-Loads any textures / resources
*************************************************/
void DarkSeed::InitGame() { 
	gameMode = GameModes::MAIN_MENU;
		
    // HACK - Demo sprite to test sprite engine
	//Sprites::Character *mc = new Sprites::GameSprite(L"../textures/ball-bounce-512x64.png", L"Vance", 32, 32) )

	Sprites::GameSprite *gs = new Sprites::GameSprite(L"../textures/ball-bounce-512x64.png", L"bouncingball", 64, 64);
	gs[0].IsVisible ( true );
    gs[0].CanAnimate ( true );
    gs[0].CanMove ( true );
	
	Util::SWCoordinates c;
	c.x = 0;
	c.y = 0;
	
	gs[0].AddAnimation(L"bounce", 0.5f, 8, c);
	gs->SyncPlayAnimation ( L"bounce" );

	gs[0].MoveDistance(0.5f, 0.5f, 0.5f, 0.5f);
	gs[0].Position ( ( WINDOW_WIDTH / 2 ) - ( gs->Size().width /2 ), ( WINDOW_HEIGHT / 2 ) - ( gs->Size().height / 2 ) , 0.5f );
	gs->SpriteType ( Sprites::Type::character );
        
    Sprites::GameSprite *gs2 = new Sprites::GameSprite(L"../textures/main-menu-1024x768.png", L"background", WINDOW_WIDTH, WINDOW_HEIGHT );
	gs2->SpriteType ( Sprites::Type::background );
	// TODO - Pull this out into it's own "center" function
	// Used to calculate and center the sprite
	float width = gs2->Size().width;
	float height = gs2->Size().height;

	width = WINDOW_WIDTH - width;
	height = WINDOW_HEIGHT - height;
	width /= 2;
	height /= 2;

    gs2->IsVisible ( true );
    gs2->Position (  width, height, 0.5f );

	this->windowOffsets->offsetBottom	= ( gs2->Size().height - WINDOW_HEIGHT ) / 2 ;
	this->windowOffsets->offsetTop		= ( gs2->Size().height - WINDOW_HEIGHT ) / 2 ;
	this->windowOffsets->offsetLeft		= ( gs2->Size().width - WINDOW_WIDTH ) / 2 ;
	this->windowOffsets->offsetRight	= ( gs2->Size().width - WINDOW_WIDTH ) / 2 ;

    this->gameSprites[0] = *gs2;
	this->gameSprites[1] = *gs; 
	this->LoadTextures();

} // InitGame


/************************************************
** MoveSprites()
**	Handles any incomming key presses
*************************************************/
void DarkSeed::MoveSprites(float interpolation) { 
    // Calculate the window offsets based on the current map sprite
    // TODO - there will be times when we don't need to calculate offsets (waste of time) probably want to create a flag 
    (*this->lpfMoveSprts)(gameSprites, interpolation);
} // MoveSprites

/**************************************
*** Handles incrementing the animation frame 
*** Sprites must maintain their own knowledge of FPS 
*** TODO - sprites should animate on time without having to calculate skips themselves
***************************************/
void DarkSeed::UpdateSprites() { 
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
void DarkSeed::Render() { 
    (*this->lpfRender)(this->gameSprites, 0);
}

/************************************************
** UpdateScene()
**	Calls the updatescene function 
*************************************************/
void DarkSeed::UpdateScene() { 
    (*this->lpfUpdateSc)(this->gameSprites);
}

void DarkSeed::LoadTextures() { 
    // Sprites to load textures for
    (*this->lpfLoadTxtrs)(this->gameSprites);
}