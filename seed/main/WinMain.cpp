// My Headers
#include "../sprites/GameSprite.h"
#include "../sprites/SpriteUtils.h"
#include "../sprites/FontSprite.h"
#include "GameModes.h"
#include "../input/XGamePad.h"
#include "DXDrawing.h"
#include "../gui/GameWindow.h"
#include "../util/TextureHandler.h"
#include "../util/Time.h"
#include "../gui/StartMenu.h"
#include "../font/GameFonts.h"
#include "GameMain.h"
#include "../sprites/base/FrameAnimation.h"

using namespace Input;
using namespace Sprites;
using namespace GameUtil;
using namespace Seed;

// GLOBALS ////////////////////////////////////
HWND wndHandle;

// D3D GLOBALS ////////////////////////////////
ID3D10Device* pD3DDevice = NULL;
IDXGISwapChain* pSwapChain = NULL;
ID3D10RenderTargetView* pRenderTargetView = NULL;
D3DXMATRIX matProjection;
D3D10_VIEWPORT m_viewPort;

// Blend State
ID3D10BlendState* pBlendState10 = NULL;
ID3D10BlendState* pOriginalBlendState10 = NULL;
ID3D10BlendState* pFontOriginalBlendState10 = NULL;

// Shader Resource View
ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

// Sprite stuff
TextureHandler* pTextureHandler = NULL;
ID3DX10Sprite* pSpriteObject = NULL;
D3DX10_SPRITE  spritePool[NUM_POOL_SPRITES];
ID3DX10Font* pGameFont = NULL;
int numActiveSprites;

// Configure the xbox controller stuff
XGamePad* xControl;

// Game Mode
GameModes::modes GAMEMODE = GameModes::MAIN_MENU;

// Windowing stuff //////////////////////////////
WindowOffsets windowOffsets;           // Determins the offsets for up/right/down/left 

// Prototypes ///////////////////////////////////
void Render(GameSprite*, int);
void UpdateScene(GameSprite*);
void MoveSprites(GameSprite*, float);
bool InitSprites();
void LoadTextures(GameSprite*);

/**************************************
*** Main Application entry point
*** 
***************************************/
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ) 
{ 
	// TODO - Implement resulation changing? Maybe? 
	/*DEVMODE dm = { 0 };
	dm.dmSize = sizeof(dm);
	for (int iModeNum = 0; EnumDisplaySettings( NULL, iModeNum, &dm ) != 0; iModeNum++) { 
		
	}*/

    // Setup the main game loop / rendering funciton
	ZeroMemory(&windowOffsets, sizeof(WindowOffsets));
    GameMain* gameMain = new GameMain();
    gameMain->lpfRender = (RENDER)Render;
    gameMain->lpfUpdateSc = (UPDATE)UpdateScene;
    gameMain->lpfMoveSprts = (MOVE)MoveSprites;
    gameMain->windowOffsets = &windowOffsets;
    gameMain->lpfLoadTxtrs = (LOADTX)LoadTextures;

	// Initialize the window
	if (!InitWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, &wndHandle) ) {
		return false;
	}
	if (!InitDirect3D(wndHandle, WINDOW_WIDTH, WINDOW_HEIGHT) ) {
		return 0;
	}
	if (!InitSprites()) {
		return 0;
	}
	// startup the controller checking
	 xControl = new XGamePad();

	// Main message loop
	MSG msg = {0};
	
	// Prime the message structure
	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);
	
	// Get the timer frequency
	int loops = 0;
	float interpolation = 0;
	float next_game_tick = ::Time::GetMilis();

	// Initialize the game!
	gameMain->InitGame();

    // Get the current time in milis
    int countLoops = 0;

    LONGLONG curTime;
    LONGLONG perfCnt;
    LONGLONG nextTime;
    DWORD    timeCount;

    QueryPerformanceFrequency((LARGE_INTEGER *) &perfCnt);
    timeCount = perfCnt / TICKS_PER_SECOND;
    QueryPerformanceCounter((LARGE_INTEGER *) &nextTime);

	wchar_t buffer[100];

	float start = Time::GetMilis();

	while (WM_QUIT != msg.message) {
		while (PeekMessage(&msg, NULL, 0,0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Detects the xbox controllers
		xControl->GetControllerStates();
		
		loops = 0;
        QueryPerformanceCounter((LARGE_INTEGER *) &curTime);
		while ( Time::GetMilis() > next_game_tick && loops <= MAX_FRAMESKIP ) { 
			//swprintf_s(buffer, 100, L"Current Loop: %d and current time: %.0f\n", countLoops, Time::GetMilis());
			//OutputDebugString(buffer); 

			gameMain->UpdateScene();
			gameMain->UpdateSprites();

            next_game_tick += SKIP_TICKS;
			if (countLoops >= TICKS_PER_SECOND) { 
				float end = Time::GetMilis();
				swprintf_s(buffer, 100, L"Started at: %.0f ended at %.0f for a diff of %.02f\n", start, end, (end - start));
				OutputDebugString(buffer);
				start = end;
				countLoops = -1;
				//return 1;
			}
			loops++;
            countLoops++;
		}

    	// Render the sprites to the screen
        gameMain->Render();

		// Moves the sprites around directionaly
		interpolation = float ( Time::GetMilis() + SKIP_TICKS - next_game_tick ) / float ( SKIP_TICKS );
		gameMain->MoveSprites(interpolation);
	}

	// Clean up the resources we allocated
	ShutdownDirect3D();
    delete gameMain;
	return (int)msg.wParam;
}

/*******************************************
** Render (D3DX10_SPRITE* spritePool, int SpritesToRender
**  Renders the sprites to the buffer which is in turn displayed on screen
** 
********************************************/
void Render(GameSprite* sprites, int spritesToRender) { 
    FLOAT OriginalBlendFactor[4];
    UINT  OriginalSampleMask = 0;
	if (pD3DDevice != NULL) {
		// Clear the target buffer
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		if (pSpriteObject != NULL) {
			// Start Drawing the sprites
			pSpriteObject->Begin(NULL);

   			// Push the DX Sprites into the sprite pool
            int c = 0;
			int i = 0;
            while(i < MAX_SPRITES ) { 
                if (sprites[i].IsVisible() && sprites[i].TextureLoaded()) { 
                    spritePool[c] = sprites[i].dxSprite;
                    c++;
                }
				i++;
            }

			/*D3DXMATRIX matScaling;
			D3DXMATRIX matTranslation;

			D3DXMatrixScaling(&matScaling, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
			D3DXMatrixTranslation(&matTranslation, 
				(float)0 + (WINDOW_WIDTH/2), 
				(float)(WINDOW_HEIGHT - 0 - (WINDOW_HEIGHT/2)), 
				0.1f);	// ZOrder

			// ID3D10Texture2D * ballBounce = NULL;
			// ballBounce = TextureHandler::GetTexture2DFromFile(L"../textures/main-menu-1024x768.png", pD3DDevice);
			// ID3D10ShaderResourceView * srv;
			// TextureHandler::GetResourceViewFromTexture(ballBounce, &srv, pD3DDevice);
			// ballBounce->Release();
			D3DX10_SPRITE sprite;
			sprite.pTexture = NULL; // srv;
			sprite.ColorModulate = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			sprite.TexCoord.x = 0;
			sprite.TexCoord.y = 0;
			sprite.TexSize.x = 1.0f;
			sprite.TexSize.y = 1.0f;
			sprite.TextureIndex = 0;
			sprite.matWorld = matScaling * matTranslation;*/


            pSpriteObject->DrawSpritesBuffered(spritePool, numActiveSprites);

            // Draw the text on top
/*			c = 0;
			while (c < MAX_SPRITES) { 
				if ((sprites + c)->sprite.kindOf == Type::font)
					DrawTextNow(pGameFont, pSpriteObject, (sprites + c)->Position().x, (sprites + c)->Position().y, ((FontSprite*)(sprites + c))->message.c_str());
				c++;
			}*/

			// Save the current blend state
			pD3DDevice->OMSetBlendState(pBlendState10, OriginalBlendFactor, 0xffffffff);

			if (pBlendState10) {
				FLOAT NewBlendFactor[4] = {0,0,0,0};
				pD3DDevice->OMSetBlendState(pBlendState10, NewBlendFactor, 0xffffffff);
			}

			// Finish up and send the sprites to the hardware
			pSpriteObject->Flush();
			pSpriteObject->End();
			
			// Restore the previous blend state
			pD3DDevice->OMSetBlendState(pOriginalBlendState10, OriginalBlendFactor, OriginalSampleMask);
			
			// display the next item in the swap chain
			pSwapChain->Present(0,0);
		}
	}
} // Render

/**************************************
*** updates the texture locations and orients the sprites to the world 
*** 
***************************************/
//float rotate = -0.0174532925f;
void UpdateScene(GameSprite* sprites) {
	D3DXMATRIX matScaling;
	D3DXMATRIX matTranslation;

	int curPoolIndex = 0;

	// loop through the sprite
	for (int i = 0; i < MAX_SPRITES; i++) {
		// Only update visible sprites
		if (sprites[i].IsVisible()) {
			// Set the proper scale for the sprite
			D3DXMATRIX matScaling;
			D3DXMATRIX matTranslation;

			D3DXMatrixScaling(&matScaling, 
                sprites[i].Size().width * sprites[i].scale.x, 
                sprites[i].Size().height * sprites[i].scale.y, 
                sprites[i].Position().z);
			D3DXMatrixTranslation(&matTranslation, 
				(float)sprites[i].Position().x + (sprites[i].Size().width/2), 
				(float)(WINDOW_HEIGHT - sprites[i].Position().y - (sprites[i].Size().height/2)), 
				0.1f);	// ZOrder

			// TODO - Refactor this out into its own function
			/* 
			D3DXMATRIX matRotate;
			D3DXMATRIX final;
			
			//matRotate = matScaling * matTranslation;
			D3DXMatrixRotationZ(&matRotate, rotate);
			rotate -= 0.0174532925f;

			final = (matScaling * matRotate) * matTranslation;
			//final = matScaling * matTranslation;
			gameSprites[i].matWorld = final;
			*/ 
			sprites[i].dxSprite.matWorld = (matScaling * matTranslation);
			
			// Animate the sprite
			if (sprites[i].CanAnimate()) {
                float curFrame = sprites[i].CurFrame();
                float numFrames = sprites[i].NumFrames();
                float div = curFrame / numFrames;
                float texCoordX = div; 
                float texSizeX = (float)(sprites[i].Size().width / (sprites[i].Size().width * sprites[i].NumFrames()));
				sprites[i].dxSprite.TexCoord.x = texCoordX;
				sprites[i].dxSprite.TexSize.x = texSizeX;
			}
			
			// Increment the pool index
			curPoolIndex++;
		}
	}

	// Update the number of active sprites
	numActiveSprites = curPoolIndex;
} // UpdateScene 

/*****************************************************
**  MoveSprites
**      Moves the sprites around the screen and translates the world as necessary
**
*****************************************************/
void MoveSprites(GameSprite* sprites, float interpolation) { 
    // We want to move a moveable sprite of course! 
	for (int i = 0; i < MAX_SPRITES; i++) {
        if (sprites[i].IsVisible() && sprites[i].CanMove()) { 
            
			// Check to see which direction was pressed
			float posY = sprites[i].Position().y;
			float posX = sprites[i].Position().x;
                
            float moveU = sprites[i].MoveDistance().up * interpolation;
            float moveD = sprites[i].MoveDistance().down * interpolation;
            float moveR = sprites[i].MoveDistance().right * interpolation;
            float moveL = sprites[i].MoveDistance().left * interpolation;

			float actualHeight = posY + sprites[i].Size().height;
			float actualWidth = posX + sprites[i].Size().width;

			// TODO - Create a means to pause
			if (xControl->IsButtonPressedForController(0, GameControls::XboxController::BACK))
				PostQuitMessage(0);

			float actualWindowBottom = WINDOW_HEIGHT;
            float actualWindowTop = 0;
            float actualWindowLeft = 0;
            float actualWindowRight = WINDOW_WIDTH;

            // Left & Right Offsets
            if (windowOffsets.offsetLeft < 0) 
                actualWindowLeft -= windowOffsets.offsetLeft;
            if (windowOffsets.offsetRight < 0) 
                actualWindowRight += windowOffsets.offsetRight; 

            // Top & Bottom Offsets
            if (windowOffsets.offsetTop < 0)
                actualWindowTop -= windowOffsets.offsetTop;
			if (windowOffsets.offsetBottom < 0)
				actualWindowBottom += windowOffsets.offsetBottom;

			// Direction is right
            if (xControl->IsButtonPressedForController(0, GameControls::XboxController::DPAD_RIGHT)) { 
				posX += moveR;
                if (actualWidth >= actualWindowRight && windowOffsets.offsetRight <= 0) {
                    posX = actualWindowRight - sprites[i].Size().width;
                } else { 
                    if (windowOffsets.offsetRight > 0 && actualWidth >= actualWindowRight) { 
                        windowOffsets.offsetRight -= moveR;
                        windowOffsets.offsetLeft += moveR;

                        // Translate the world to the right
                        ::SpriteUtil::TranslateSprites((moveR *-1),0,sprites,i);
                        // Ensure our sprite doesn't go beyond the right edge
                        posX -= moveR;
                    }
                }
            } // Translate for Right

			// Direciton is left
			if (xControl->IsButtonPressedForController(0, GameControls::XboxController::DPAD_LEFT)) { 
				posX -= moveL;

                if (posX <= actualWindowLeft && windowOffsets.offsetLeft <= 0) {
                    posX = actualWindowLeft;
                } else { 
                    if (windowOffsets.offsetLeft > 0 && posX <= 0) { 
                        windowOffsets.offsetRight += moveL;
                        windowOffsets.offsetLeft -= moveL;

                        // Translate the world to the right
                        ::SpriteUtil::TranslateSprites((moveL),0,sprites,i);
                        // Ensure our sprite doesn't go beyond the left edge
                        posX += moveL;
                    }
                }
            } // Translate for left

            // Direction is down
			if (xControl->IsButtonPressedForController(0, GameControls::XboxController::DPAD_DOWN)) {
				posY += moveD;
				if ( actualHeight >= actualWindowBottom && windowOffsets.offsetBottom <= 0) { 
					posY = actualWindowBottom - sprites[i].Size().height;
				} else { 
					// Check our _offsetBottom if it is a positive nbr we can translate the world up
					if (windowOffsets.offsetBottom > 0 && actualHeight >= actualWindowBottom) {
						windowOffsets.offsetBottom -= moveD;
						windowOffsets.offsetTop += moveD;

						// Translate the world up
                        ::SpriteUtil::TranslateSprites(0, (moveD * -1), sprites, i);
						// ensure our sprite doesn't go below the bottom edge
						posY -= moveD;
					} 
				}
			} // Translate for down

            // Direction is up 
            if (xControl->IsButtonPressedForController(0, GameControls::XboxController::DPAD_UP)) {
				posY -= moveU;

                if (posY <= actualWindowTop && windowOffsets.offsetTop <= 0) { 
                    posY = actualWindowTop;
                } else { 
                    // check out _offsetTop if it is a positive nbr we can translate the world down
                    if (windowOffsets.offsetTop > 0 && posY <= 0) { 
                        windowOffsets.offsetBottom += moveU;
                        windowOffsets.offsetTop -= moveU;

                        // Translate the world down
                        ::SpriteUtil::TranslateSprites(0, moveU, sprites, i);
                        posY += moveU;
                    }
                }
            } // Translate for up

			sprites[i].Position ( posX, posY, sprites[i].Position().z );
		}

        // One final check to see if the sprite is no longer in the visible range
        sprites[i].IsVisible ( SpriteUtil::IsSpriteVisible ( &sprites[i] ) );
	}
} // MoveSprites

/*******************************************
***    Loads the textures for the sprites
***    
*******************************************/
void LoadTextures(GameSprite* sprites) {
	int i = 0; 
	while (i < MAX_SPRITES) {
        if (sprites[i].IsVisible() && !sprites[i].TextureLoaded()) { 
			// Check and load textures for any sprites that still need it
			ID3D10Texture2D* texture = NULL;
            if (sprites[i].kindOf != Type::color) {
                texture = TextureHandler::GetTexture2DFromFile(sprites[i].Resource(), pD3DDevice);
			}

			ID3D10ShaderResourceView* srv = NULL;
			if (texture) { 
				TextureHandler::GetResourceViewFromTexture(texture, &srv, pD3DDevice);
				texture->Release();
				texture = NULL;
			}

			// Set the srv into the poolSprite
            sprites[i].dxSprite.pTexture = srv;
			sprites[i].dxSprite.TextureIndex = 0;
			sprites[i].dxSprite.TexCoord.x = 0;
			sprites[i].dxSprite.TexCoord.y = 0;
			sprites[i].dxSprite.TexSize.x = 1.0f;
			sprites[i].dxSprite.TexSize.y = 1.0f;
			sprites[i].dxSprite.ColorModulate = sprites[i].color; // D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
            sprites[i].TextureLoaded ( true );
		}
		i++;
	}
} // LoadTextures




/**************************************
*** creates the inital sprites either on game start or transition 
*** 
***************************************/
bool InitSprites() {
    // Create the sprite object (calls methods to display the sprites)
	if (D3DX10CreateSprite(pD3DDevice, 0, &pSpriteObject) != S_OK) {
		return false;
	}

	// Enable blending
	D3D10_BLEND_DESC StateDesc; 
	InitiateDefaultBlend(&StateDesc);
	pD3DDevice->CreateBlendState(&StateDesc, &pBlendState10);

	// Set the projection matrix
	if (pSpriteObject->SetProjectionTransform(&matProjection) != S_OK) {
		return false;
	}

	return true;
} // InitSprites


/*******************************************
***    For starting and shutting down
***    The directx interface
*******************************************/
bool InitDirect3D(HWND hWnd, int windowWidth, int windowHeight) {
	
	// Create the clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = windowWidth;
	swapChainDesc.BufferDesc.Height = windowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the D3D device and the swap chain
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
												D3D10_DRIVER_TYPE_HARDWARE, // IF this is anything other than hardware, GAME WILL SUCK
												NULL,
												0,
												D3D10_SDK_VERSION,
												&swapChainDesc,
												&pSwapChain,
												&pD3DDevice);

	// Ensure the device was created
	if (hr != S_OK) {
		MessageBox(hWnd, TEXT("A DX10 Compliant Video Card is Required"), TEXT("ERROR"), MB_OK);
		return false;
	}

	// Get the back buffer from the swapchain
	ID3D10Texture2D *pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer);
	if (hr != S_OK) {
		return false;
	}
	// Create the render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	// Release the back buffer
	pBackBuffer->Release();

	// Make sure the render target view was created successfully
	if (hr != S_OK) {
		return false;
	}

	 // Set the render target
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// Create and set the viewport
	m_viewPort;
	m_viewPort.Width = windowWidth;
	m_viewPort.Height = windowHeight;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;
	m_viewPort.TopLeftX = 0;
	m_viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &m_viewPort);
	
	D3DXMatrixOrthoOffCenterLH(&matProjection, 
		(float)m_viewPort.TopLeftX, 
		(float)m_viewPort.Width, 
		(float)m_viewPort.TopLeftY, 
		(float)m_viewPort.Height, 
		0.1f, 
		10);

	return true;
} // InitDirect3D

/**************************************
*** Shuts down the Direct3D Interface
***
***************************************/
void ShutdownDirect3D() {
	// Release the original blend state object
	if (pOriginalBlendState10 != NULL){
		pOriginalBlendState10->Release();
		pOriginalBlendState10 = NULL;
	}

	// Release the blend state object
	if (pBlendState10 != NULL)	{
		pBlendState10->Release();
		pBlendState10 = NULL;
	}

    // release the ID3DX10Sprite object
    if (pSpriteObject)    {
        pSpriteObject->Release();
        pSpriteObject = NULL;
    }

	// release the rendertarget
	if (pRenderTargetView) 	{
		pRenderTargetView->Release();
	}

	// release the swapchain
    if (pSwapChain)	{
		pSwapChain->Release();
	}

	// release the D3D Device
    if (pD3DDevice)	{
		pD3DDevice->Release();
	}
} // ShutdownDirect3D
/* eof */