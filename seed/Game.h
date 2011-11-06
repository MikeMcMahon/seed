#pragma once

// #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#define STRICT
#define WINVER       0x500

// Required for rendering stuff on time
#define TICKS_PER_SECOND 60
#define MAX_FRAMESKIP 5

// Sprite calcs
#define MAX_SPRITES			2048

// Window handling stuff
#define WINDOW_WIDTH 1028
#define WINDOW_HEIGHT 768
#define CLASS_NAME TEXT("Dark Seed")

#if _DEBUG
    #define DIRECTORY_PREFIX "../"
#else 
    #define DIRECTORY_PREFIX "./"
#endif

#include <Windows.h>
#include <WindowsX.h>

#include <D3D10.h>
#include <D3DX10.h>
#include <XInput.h>

#include <tchar.h>
#include <vector>
#include <string>

#include <SpriteWorks2D.h>
/* eof */