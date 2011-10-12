#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
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

#include <comutil.h>
#include <XmlHelper.h>

// Required for rendering stuff on time
#define TICKS_PER_SECOND 60
#define SKIP_TICKS (1000.0f / (float)TICKS_PER_SECOND)
#define MAX_FRAMESKIP 5

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define CLASS_NAME TEXT("SEED")

#if _DEBUG
    #define DIRECTORY_PREFIX "../"
#else 
    #define DIRECTORY_PREFIX "./"
#endif