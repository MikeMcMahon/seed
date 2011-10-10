#pragma once

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
bool InitWindow( HINSTANCE hInstance, int windowWidth, int windowHeight, HWND* windowHandle); 

struct WindowOffsets { 
    float offsetTop;
    float offsetRight;
    float offsetBottom;
    float offsetLeft;
};
/* eof */