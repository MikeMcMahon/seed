#include "GameFonts.h"

bool InitFont(ID3D10Device* device, ID3DX10Font* font, int height, UINT width, UINT fontWeight, LPCWSTR fontFace) { 

	HRESULT hr = D3DX10CreateFont(
		device,
		height, width,
		fontWeight,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		fontFace,
		&font);

	if (FAILED(hr)) { 
		return false;
	}

	return true;
}