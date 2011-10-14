#pragma once

#include "../sprites/GameSprite.h"

void InitiateDefaultBlend(D3D10_BLEND_DESC *);
bool InitDirect3D( HWND hWnd, int, int);
int LoadTexturesForSprites();
void ShutdownDirect3D();
/* eof */