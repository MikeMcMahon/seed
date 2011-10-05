#include "GameHeaders.h"		// Includes all of those fancy external things like DX10 :) 

// My Headers
#include "sprites\CharacterSprite.h"
#include "sprites\MapSprite.h"
#include "sprites\TileSprite.h"

#include "GameModes.h"
#include "input\XGamePad.h"
#include "DXDrawing.h"
#include "GameWindow.h"

using namespace input;
using namespace sprites;

// GLOBALS ////////////////////////////////////
HWND wndHandle;
int numActiveSprites = 0;
GameSprite gameSprites[MAX_SPRITES];

// D3D GLOBALS ////////////////////////////////
ID3D10Device* pD3DDevice = NULL;
IDXGISwapChain* pSwapChain = NULL;
ID3D10RenderTargetView* pRenderTargetView = NULL;
D3DXMATRIX matProjection;

// Blend State
ID3D10BlendState* pBlendState10 = NULL;
ID3D10BlendState* pOriginalBlendState10 = NULL;

// Shader Resource View
ID3D10ShaderResourceView * gSpriteTextureRV = NULL;

// Sprite stuff
ID3DX10Sprite *pSpriteObject = NULL;
D3DX10_SPRITE  spritePool[NUM_POOL_SPRITES];

// Configure the xbox controller stuff
XGamePad* xControl;

// Game Mode
GameModes::MODES GAMEMODE = GameModes::MAIN_MENU;

// Windowing stuff //////////////////////////////
float _offsetLeft = 0;
float _offsetRight = 0;
float _offsetTop = 0;
float _offsetBottom = 0;

void Render();
void UpdateScene();
void MoveSprites(float);
void UpdateSprites(); 
bool InitSprites();
bool HasFrameElapsed(); 

float GetMilis();
float GetMilis() {
	
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);

	// Return in Miliseconds
	return ((float)t.QuadPart / (float)f.QuadPart) * 1000.0f;
}


// Main entry point
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ) 
{
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
	float next_game_tick = GetMilis();
	while (WM_QUIT != msg.message) {
		while (PeekMessage(&msg, NULL, 0,0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Detects the xbox controllers
		xControl->GetControllerStates();
		
		loops = 0;
		while ( GetMilis() > next_game_tick && loops < MAX_FRAMESKIP) { 
			// Handles the textures / animation
			UpdateScene();
			UpdateSprites();
		
			next_game_tick += SKIP_TICKS;
			loops++;
		}

		interpolation = float ( GetMilis() + SKIP_TICKS - next_game_tick ) / float ( SKIP_TICKS );
		// Moves the sprites around directionaly
		MoveSprites(interpolation);		

		// Render the sprites to the screen
		Render();
	}

	// Clean up the resources we allocated
	ShutdownDirect3D();
	return (int)msg.wParam;
}

void Render() {
	FLOAT OriginalBlendFactor[4];
    UINT  OriginalSampleMask = 0;
	if (pD3DDevice != NULL) {
		// Clear the target buffer
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		
		
		if (pSpriteObject != NULL) {
			// Start Drawing the sprites
			pSpriteObject->Begin(D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK);
			
			// Copy the sprites into the spritePool
			for (int i = 0; i < MAX_SPRITES; i++) {
				spritePool[i] = gameSprites[i];
			}
			
			// Draw all of the sprites in the pool
			pSpriteObject->DrawSpritesBuffered(spritePool, 2);

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
}

void UpdateScene() {
	D3DXMATRIX matScaling;
	D3DXMATRIX matTranslation;

	int curPoolIndex = 0;

	// loop through the sprite
	for (int i = 0; i < MAX_SPRITES; i++) {
		// Only update visible sprites
		if (gameSprites[i].isVisible()) {
			// Set the proper scale for the sprite
			D3DXMATRIX matScaling;
			D3DXMATRIX matTranslation;

			D3DXMatrixScaling(&matScaling, gameSprites[i].spriteSize().width, gameSprites[i].spriteSize().height, gameSprites[i].position().z);
			D3DXMatrixTranslation(&matTranslation, 
				(float)gameSprites[i].position().x + (gameSprites[i].spriteSize().width/2), 
				(float)(WINDOW_HEIGHT - gameSprites[i].position().y - (gameSprites[i].spriteSize().height/2)), 
				0.1f);	// ZOrder

			// Update the sprites position and scale
			gameSprites[i].matWorld = matScaling * matTranslation;

			// Animate the sprite
			if (gameSprites[i].canAnimate()) {
				float texCoordX = (float)(gameSprites[i].curFrame() / gameSprites[i].animationDetail().numFrames);
				float texSizeX = (float)(gameSprites[i].spriteSize().width / (gameSprites[i].spriteSize().width * gameSprites[i].animationDetail().numFrames));
				gameSprites[i].TexCoord.x = texCoordX;
				gameSprites[i].TexSize.x = texSizeX;
			}
			
			// Increment the pool index
			curPoolIndex++;
		}
	}

	// Update the number of active sprites
	numActiveSprites = curPoolIndex;
}

// InitSprites!
bool InitSprites() {
	// Absofuckingloutely required or the sprites will not display - this is required because we need to ensure the sprite struct is CLEAN Before sending to the renderer
	ZeroMemory(gameSprites, MAX_SPRITES * sizeof(GameSprite));

	ID3D10Texture2D * backgroundTexture = NULL;
	switch (GAMEMODE) { 
	case GameModes::MAIN_MENU:
		// Load the background texture
		backgroundTexture = GetTexture2DFromFile("./textures/large-background-png-1000-800.png", pD3DDevice);
		if (backgroundTexture == NULL) return false;
		GetResourceViewFromTexture(backgroundTexture, &gSpriteTextureRV, pD3DDevice);
		backgroundTexture->Release();
		break;
	default:
		return false;
	}

	// Create the sprite object (calls methods to display the sprites)
	HRESULT hr = D3DX10CreateSprite(pD3DDevice, 0, &pSpriteObject);
	if (hr != S_OK) {
		return false;
	}

	// Enable blending
	D3D10_BLEND_DESC StateDesc; 
	InitiateDefaultBlend(&StateDesc);
	pD3DDevice->CreateBlendState(&StateDesc, &pBlendState10);


	// Create another texture for the bouncing ball
	ID3D10Texture2D * ballBounce = NULL;
	ballBounce = GetTexture2DFromFile("./textures/ball_bounce_512x64.png", pD3DDevice);
	ID3D10ShaderResourceView * srv;
	GetResourceViewFromTexture(ballBounce, &srv, pD3DDevice);
	ballBounce->Release();

	GameSprite gp;
	(&gp)->spriteSize(64, 64);
	(&gp)->curFrame(0);
	(&gp)->animationDetail(0, 8, 0.5f);
	(&gp)->pTexture = srv;
	(&gp)->TexCoord.x = 0;
	(&gp)->TexCoord.y = 0;
	(&gp)->TexSize.x = 1.0f;
	(&gp)->TexSize.y = 1.0f;
	(&gp)->TextureIndex = 0;
	(&gp)->ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	(&gp)->position(
		((float)WINDOW_WIDTH/2.0f) - (float)gp.spriteSize().width / 2.0f,		// Moves the sprite to the center of the x axis
		((float)WINDOW_HEIGHT/2.0f) - (float)gp.spriteSize().height / 2.0f,		// Move the sprite to the center of the y axis
		0.5f);
	(&gp)->setMoveDistance(0.5f,0.5f);
	(&gp)->isVisible(TRUE);
	(&gp)->canAnimate(TRUE);

	// Texture for this sprite to use
	GameSprite cp;
	(&cp)->spriteSize(800, 1000);

	// Set the offsets for the sprites moving around
	_offsetBottom = (cp.spriteSize().height - WINDOW_HEIGHT) / 2.0f;
	_offsetTop = _offsetBottom;
	_offsetLeft = (cp.spriteSize().width - WINDOW_WIDTH) / 2.0f;
	_offsetRight = _offsetLeft;

	(&cp)->curFrame(0);
	(&cp)->animationDetail(0, 8, 0.5f);
	(&cp)->pTexture = gSpriteTextureRV;
	(&cp)->TexCoord.x = 0;
	(&cp)->TexCoord.y = 0;
	(&cp)->TexSize.x = 1.0f;
	(&cp)->TexSize.y = 1.0f;
	(&cp)->TextureIndex = 0;
	(&cp)->ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	(&cp)->position(
		((float)WINDOW_WIDTH/2.0f) - (float)cp.spriteSize().width / 2.0f,		// Moves the sprite to the center of the x axis
		((float)WINDOW_HEIGHT/2.0f) - (float)cp.spriteSize().height / 2.0f,		// Move the sprite to the center of the y axis
		0.5f);
	(&cp)->setMoveDistance(0.5f,0.5f);
	(&cp)->isVisible(TRUE);
	(&cp)->canAnimate(FALSE);

	

	gameSprites[0] = gp;
	gameSprites[1] = cp;

	// Set the projection matrix
	if (pSpriteObject->SetProjectionTransform(&matProjection) != S_OK) {
		return false;
	}

	return true;
}


void UpdateSprites() { 
	for (int i = 0; i < MAX_SPRITES; i++) { 
		if (gameSprites[i].isVisible() && gameSprites[i].canAnimate()) { 
			gameSprites[i].incrementFrame();

			// reset the frames if we're past the max # of frames
			if (gameSprites[i].curFrame() >= gameSprites[i].animationDetail().numFrames) { 
				gameSprites[i].curFrame(0);
			}
		}
	}
}
D3D10_VIEWPORT m_viewPort;
float topLeftX, topLeftY, width, height;
void MoveSprites(float interpolation) { 
	// We want to move a moveable sprite of course! 
	for (int i = 0; i < MAX_SPRITES; i++) {
		if (gameSprites[i].isVisible() && gameSprites[i].canAnimate()) { 
			// Check to see which direction was pressed
			float posY = gameSprites[i].position().y;
			float posX = gameSprites[i].position().x;
			float moveX = gameSprites[i].getMoveX() * interpolation;
			float moveY = gameSprites[i].getMoveY() * interpolation;
			float actualHeight = posY + gameSprites[i].spriteSize().height;
			float actualWidth = posX + gameSprites[i].spriteSize().width;

			// Can the sprite run? we should check that first :) 
			if (xControl->IsButtonPressedForController(0, A_BUTTON)) {
				moveX *= 2.5f;
				moveY *= 2.5f;
			}

			if (xControl->IsButtonPressedForController(0, DPAD_UP))
				posY -= moveY;
			if (xControl->IsButtonPressedForController(0, DPAD_RIGHT)) 
				posX += moveX;
			if (xControl->IsButtonPressedForController(0, DPAD_LEFT)) 
				posX -= moveX;

			// Temp for debugging
			if (xControl->IsButtonPressedForController(0, input::BACK))
				PostQuitMessage(0);

			float actualWindowHeight = WINDOW_HEIGHT;
			if (_offsetBottom < 0) { 
				// We have negative space on the screen we cannot traverse
				actualWindowHeight += _offsetBottom;
			}

			// Direction is down
			if (xControl->IsButtonPressedForController(0, DPAD_DOWN)) {
				posY += moveY;
				if ( actualHeight > actualWindowHeight && _offsetBottom <= 0) { 
					posY = actualWindowHeight - gameSprites[i].spriteSize().height;
				} else { 
					// Check our _offsetBottom if it is a positive nbr we can translate the world up
					if (_offsetBottom > 0 && actualHeight >= actualWindowHeight) {
						_offsetBottom -= moveY;
						_offsetTop += moveY;

						// Move the background up
						// TODO - Write a method that translates everything, not just statically known sprite
						gameSprites[1].position(
							gameSprites[1].position().x, 
							gameSprites[1].position().y-moveY,
							gameSprites[1].position().z);

						// ensure our sprite doesn't go below the bottom edge
						posY -= moveY;
					} 
				}
			}

			// Direction is up 
			if ( (posY <= 0) ) { 
				// TODO - translate the world down
				posY = 0;
			}

			// Direction is right
			if ( actualWidth > WINDOW_WIDTH )  {
				posX -= moveX;
			}

			// Direction is left
			if ( (posX < 0) ) { 
				// TODO - translate the world to the right
				posX = 0;
			}

			gameSprites[i].position(posX, posY, gameSprites[i].position().z);
		}
	}
}



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

	topLeftX = 0;
	topLeftY = 0;
	width = windowWidth;
	height = windowHeight;

	pD3DDevice->RSSetViewports(1, &m_viewPort);
	
	D3DXMatrixOrthoOffCenterLH(&matProjection, 
		(float)m_viewPort.TopLeftX, 
		(float)m_viewPort.Width, 
		(float)m_viewPort.TopLeftY, 
		(float)m_viewPort.Height, 
		0.1f, 
		10);

	return true;
}

void ShutdownDirect3D() {
	// Release the original blend state object
	if (pOriginalBlendState10 != NULL)
	{
		pOriginalBlendState10->Release();
		pOriginalBlendState10 = NULL;
	}

	// Release the blend state object
	if (pBlendState10 != NULL)
	{
		pBlendState10->Release();
		pBlendState10 = NULL;
	}

    // release the ID3DX10Sprite object
    if (pSpriteObject)
    {
        pSpriteObject->Release();
        pSpriteObject = NULL;
    }

	// release the rendertarget
	if (pRenderTargetView) 
	{
		pRenderTargetView->Release();
	}

	// release the swapchain
    if (pSwapChain)
	{
		pSwapChain->Release();
	}

	// release the D3D Device
    if (pD3DDevice) 
	{
		pD3DDevice->Release();
	}
}
