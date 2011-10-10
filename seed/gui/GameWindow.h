#pragma once

#include "../main/GameConstants.h"
#include <Windows.h>
#include <WindowsX.h>

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
bool InitWindow( HINSTANCE hInstance, int windowWidth, int windowHeight, HWND* windowHandle); 

struct WindowOffsets { 
    float offsetTop;
    float offsetRight;
    float offsetBottom;
    float offsetLeft;
};
/* eof */