#pragma once

#include <D3D10.h>
#include <D3DX10.h>

void InitiateDefaultBlend(D3D10_BLEND_DESC *);
bool InitDirect3D( HWND hWnd, int, int);
void ShutdownDirect3D();
/* eof */