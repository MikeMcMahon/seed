#pragma once

#define HELVETICA L"Helvetica"
#define TIMES L"Times"
#define ARIAL L"Arial"

#define SZ_TINY   10
#define SZ_NORMAL 20
#define SZ_LARGE  30
#define SZ_HUGE   40

#define FNT_BLACK D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define FNT_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define FNT_GRAY  D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f)

bool InitFont(ID3D10Device* device, ID3DX10Font** font, int height, UINT width, UINT fontWeight, LPCWSTR fontFace);
void DrawTextNow(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, float x, float y, LPCSTR text, D3DXCOLOR color = FNT_BLACK);
void FontRect(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, RECT* rect, float x, float y, LPCWSTR text);