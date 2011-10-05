#include "GameHeaders.h"

void InitiateDefaultBlend(D3D10_BLEND_DESC *);
ID3D10Texture2D* GetTexture2DFromFile(LPCSTR, ID3D10Device*);
void GetResourceViewFromTexture(ID3D10Texture2D*, ID3D10ShaderResourceView **, ID3D10Device*);
bool InitDirect3D( HWND hWnd, int, int);
void ShutdownDirect3D();