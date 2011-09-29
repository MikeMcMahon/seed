#include "GameHeaders.h"		// Includes all of those fancy external things like DX10 :) 

// My Headers
#include "GameSprite.h"
#include "GameModes.h"
#include "XInputControllers.h"
#include "DXDrawing.h"


// Setup the window width / height - should probably move this somewhere else at some point
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CLASS_NAME TEXT("PLATFORM-MAN")

// GLOBALS ////////////////////////////////////
HWND wndHandle;
int numActiveSprites = 0;
GameSprite sprites[MAX_SPRITES];

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
XControllers * XControl;

// Game Mode
GameModes::MODES GAMEMODE = GameModes::MAIN_MENU;

bool InitWindow( HINSTANCE hInstance, int windowWidth, int windowHeight ); 
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();
void UpdateScene();
void MoveSprites();
void UpdateSprites(); 
bool InitSprites();
bool HasFrameElapsed(); 

// Timers
LARGE_INTEGER timeStart;
LARGE_INTEGER timeEnd;
LARGE_INTEGER timerFreq;
float animRate;
float lastElapsedFrame = 0;
float frameDuration = 0.05f;

// Main entry point
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ) 
{
	
	// Initialize the window
	if (!InitWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT) ) {
		return false;
	}
	if (!InitDirect3D(wndHandle, WINDOW_WIDTH, WINDOW_HEIGHT) ) {
		return 0;
	}
	if (!InitSprites()) {
		return 0;
	}
	// startup the controller checking
	 XControl = new XControllers();

	// Main message loop
	MSG msg = {0};
	
	// Prime the message structure
	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);
	
	// Get the clock frequency
	QueryPerformanceFrequency(&timerFreq);

	// Get the timer frequency
	while (WM_QUIT != msg.message) {
		while (PeekMessage(&msg, NULL, 0,0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Detects the xbox controllers
		XControl->GetControllerStates();

		// Moves the sprites around directionaly
		MoveSprites();

		// Handles the textures animation
		UpdateScene();

		// Get the start time
		QueryPerformanceCounter(&timeStart);
		Render();
		// Get the end time
		QueryPerformanceCounter(&timeEnd);

		// set the animation rate
		animRate = ( (float)timeEnd.QuadPart - (float)timeStart.QuadPart ) / timerFreq.QuadPart;

		// Do any updating of the sprites after the scene is over
		UpdateSprites();
	}

	// Clean up the resources we allocated
	ShutdownDirect3D();
	return (int)msg.wParam;
}

bool InitWindow(HINSTANCE hInstance, int windowWidth, int windowHeight) {
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);				// the size of the structure
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;			// The window procedure callback
	wcex.cbClsExtra		= 0;							// Extra bytes to allocate for this class
	wcex.cbWndExtra		= 0;							// Extra bytes to allowcate for this instance
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;									// Icon to associate with the application
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);		// The default cursor to use
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);// Background color
	wcex.lpszMenuName	= NULL;						// The resource name of the menu (if I had one...)
	wcex.lpszClassName	= CLASS_NAME;			// Name of the class being created
	wcex.hIconSm		= 0;								// Handle of the small icon
	if (!RegisterClassEx(&wcex)) {
		return false;
	}
	
	// Resize the window
	RECT rect = { 0, 0, windowWidth, windowHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// Create the window from the class above
	wndHandle = CreateWindow(CLASS_NAME, 
		TEXT("Super Vulgar Tower Defense"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!wndHandle) { 
		return false;
	}

	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Check any available messages from the queue
	switch (message)
	{ 
		// allow the user to press the escape key to end the application
	case WM_KEYDOWN:
		switch(wParam) 
		{
		// check if the user hit the Escape key
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}



void Render() {
	FLOAT OriginalBlendFactor[4];
    UINT  OriginalSampleMask = 0;
	if (pD3DDevice != NULL) {
		// Clear the target buffer
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)); // 7-17 microseconds

		if (pSpriteObject != NULL) {
			// Start Drawing the sprites
			pSpriteObject->Begin(NULL);		// Do no sorting, we want the sprites drawn as they are in the spritePool! 

			// Copy the sprites into the spritePool
			for (int i = 0; i < MAX_SPRITES; i++) {
				spritePool[i] = sprites[i];
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
		if (sprites[i].visible) {
			// Set the proper scale for the sprite
			D3DXMATRIX matScaling;
			D3DXMATRIX matTranslation;

			D3DXMatrixScaling(&matScaling, sprites[i].width, sprites[i].height, 1.0f);
			D3DXMatrixTranslation(&matTranslation, (float)sprites[i].posX + (sprites[i].width/2), (float)(WINDOW_HEIGHT - sprites[i].posY - (sprites[i].height/2)), 0.1f);

			// Update the sprites position and scale
			sprites[i].matWorld = matScaling * matTranslation;

			// Animate the sprite
			if (sprites[i].canAnimate) {
				float texCoordX = (float)(sprites[i].curFrame / sprites[i].numFrames);
				float texSizeX = (float)(sprites[i].width / (sprites[i].width * sprites[i].numFrames));
				sprites[i].TexCoord.x = texCoordX;
				sprites[i].TexSize.x = texSizeX;
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
	ID3D10Texture2D * backgroundTexture = NULL;
	switch (GAMEMODE) { 
	case GameModes::MAIN_MENU:
		// Load the background texture
		backgroundTexture = GetTexture2DFromFile("./images/main_menu_background.png", pD3DDevice);
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

	// Texture for this sprite to use
	sprites[0].pTexture = gSpriteTextureRV;
	sprites[0].TexCoord.x = 0;		// Determin the top left location in U,V coords
	sprites[0].TexCoord.y = 0;
	sprites[0].TexSize.x = 1.0f;	// Determine the texture size in U,V coords
	sprites[0].TexSize.y = 1.0f;
	sprites[0].TextureIndex = 0;	// The texture index, single textures will use 0
	sprites[0].ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// The color to apply to the sprite

	// Set the projection matrix
	if (pSpriteObject->SetProjectionTransform(&matProjection) != S_OK) {
		return false;
	}

	sprites[0].width = WINDOW_WIDTH;
	sprites[0].height = WINDOW_HEIGHT;
	sprites[0].posX = 0;
	sprites[0].posY = 0;
	sprites[0].moveX = .05f; // How much said sprite can move in x direction at a given time
	sprites[0].moveY = .05f; // How much said sprite can move in the y direciton at a given time
	sprites[0].visible = TRUE;
	sprites[0].canAnimate = FALSE;

	return true;
}


void UpdateSprites() { 
	lastElapsedFrame += animRate;
		
	if (lastElapsedFrame < frameDuration) { 
		// Only update if it's time to update!
		return;
	}

	// Reset the frame counter
	lastElapsedFrame = 0;
	for (int i = 0; i < MAX_SPRITES; i++) { 
		if (sprites[i].visible && sprites[i].canAnimate) { 
			sprites[i].curFrame++;

			// reset the frames if we're past the max # of frames
			if (sprites[i].curFrame >= sprites[i].numFrames) { 
				sprites[i].curFrame = 0;
			}
		}
	}
}

void MoveSprites() { 
	// We want to move a moveable sprite of course! 
	if (sprites[0].visible) { 
		// Check to see which direction was pressed
		float posY = sprites[0].posY;
		float posX = sprites[0].posX;
		float moveX = sprites[0].moveX;
		float moveY = sprites[0].moveY; 

		if (XControl->IsButtonPressedForController(0, DPAD_UP))
			posY -= moveY;
		if (XControl->IsButtonPressedForController(0, DPAD_DOWN)) 
			posY += moveY;
		if (XControl->IsButtonPressedForController(0, DPAD_RIGHT)) 
			posX += moveX;
		if (XControl->IsButtonPressedForController(0, DPAD_LEFT)) 
			posX -= moveX;

		// Temp for debugging
		if (XControl->IsButtonPressedForController(0, BACK))
			PostQuitMessage(0);

		if ( (posY > WINDOW_HEIGHT) ) { 
			posY = WINDOW_HEIGHT;
		}
		if ( (posY <= 0) ) { 
			posY = 0;
		}
		if ( (posX > WINDOW_WIDTH) ) { 
			posX = WINDOW_WIDTH;
		}
		if ( (posX < 0) ) { 
			posX = 0;
		}

		sprites[0].posY = posY;
		sprites[0].posX = posX;
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
	D3D10_VIEWPORT viewPort;
	viewPort.Width = windowWidth;
	viewPort.Height = windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pD3DDevice->RSSetViewports(1, &viewPort);

	D3DXMatrixOrthoOffCenterLH(&matProjection, 
		(float)viewPort.TopLeftX, 
		(float)viewPort.Width, 
		(float)viewPort.TopLeftY, 
		(float)viewPort.Height, 
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
