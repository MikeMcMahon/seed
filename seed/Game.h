#pragma once

// #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#define STRICT
#define WINVER       0x500

#include <Windows.h>
#include <WindowsX.h>

#include <D3D10.h>
#include <D3DX10.h>
#include <XInput.h>

#include <tchar.h>
#include <vector>
#include <string>

// Required for rendering stuff on time
#define TICKS_PER_SECOND 60
#define SKIP_TICKS (1000.0f / (float)TICKS_PER_SECOND)
#define MAX_FRAMESKIP 5

// Sprite calcs
#define MAX_SPRITES			2048
#define NUM_POOL_SPRITES	MAX_SPRITES

// Window handling stuff
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define CLASS_NAME TEXT("DarkSeed")

#if _DEBUG
    #define DIRECTORY_PREFIX "../"
#else 
    #define DIRECTORY_PREFIX "./"
#endif

// Define for which engine to render against
#define RENDER_ENG_DX

/* eof */