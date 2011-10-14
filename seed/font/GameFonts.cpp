#include "GameFonts.h"

bool InitFont(ID3D10Device* device, ID3DX10Font** font, int height, UINT width, UINT fontWeight, LPCWSTR fontFace) { 
	HRESULT hr = D3DX10CreateFont(
		device,
		height, width,
		fontWeight,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		NONANTIALIASED_QUALITY, 
		DEFAULT_PITCH || FF_DONTCARE,
		fontFace,
		font);
	

	if (FAILED(hr)) { 
		return false;
	}

	return true;
}

void DrawTextNow(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, float x, float y, LPCSTR text, D3DXCOLOR color) {
	RECT rc;
	SetRectEmpty(&rc);

	// Get the rectangle dimension
	pFont->DrawTextA(pSprite,text,-1,&rc,DT_CALCRECT,color);

	// Apply the x/y if there is one
	if (x > 0) { 
		rc.left += x;
		rc.right += x;
	}
	if (y > 0) { 
		rc.top += y;
		rc.bottom += y;
	}

	// Actually draw the text
	pFont->DrawTextA(pSprite, text, -1, &rc, 0, color);
}

void FontRect(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, RECT* rect, float x, float y, LPCWSTR text) { 
	SetRectEmpty(rect);

	// Get the rectangle dimension
	pFont->DrawTextW(pSprite,text,-1,rect,DT_CALCRECT,FNT_BLACK);

	// Apply the x/y if supplied
	if (x > 0) { 
		rect->left += x;
		rect->right += x;
	}
	if (y > 0) { 
		rect->top += y;
		rect->bottom += y;
	}
}