#ifndef __GAME_H_INCLUDE__
#define __GAME_H_INCLUDE__

// Balls to the walls SON!
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WindowsX.h>
#include <tchar.h>
#include <d3d10.h>
#include <D3DX10.h>
#include <XInput.h>
#include <vector>

// Required for rendering stuff on time
const int TICKS_PER_SECOND = 60;
const float SKIP_TICKS = 1000.0f / (float)TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CLASS_NAME TEXT("PLATFORM-MAN")


#endif