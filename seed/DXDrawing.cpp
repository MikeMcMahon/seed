#include "DXDrawing.h"

void InitiateDefaultBlend(D3D10_BLEND_DESC* StateDesc) {
	ZeroMemory(StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc->AlphaToCoverageEnable = FALSE;
	StateDesc->BlendEnable[0] = TRUE;	// If this is false, DUH we can't blend
	StateDesc->SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc->DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc->BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc->SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc->DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc->BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc->RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
}


ID3D10Texture2D* GetTexture2DFromFile(LPCSTR filename, ID3D10Device* pD3DDevice) {
	ID3D10Texture2D* texture2D = NULL;
	ID3D10Resource* pD3D10Resource = NULL;

	// Loads the texture into a temporary ID3D10Resource object
	HRESULT hr = D3DX10CreateTextureFromFileA(pD3DDevice, LPCSTR(filename), NULL, NULL, &pD3D10Resource, NULL);
	if (FAILED(hr)) {
		return NULL;
	}

	// Translate the resource into a 2D texture
	pD3D10Resource->QueryInterface(__uuidof( ID3D10Texture2D), (LPVOID*)&texture2D);
	pD3D10Resource->Release();

	// REturns the ID3D10Texture2D Object
	return texture2D;
}

void GetResourceViewFromTexture(ID3D10Texture2D* texture, ID3D10ShaderResourceView **resourceView, ID3D10Device* pD3DDevice)
{
	if (texture != NULL)
	{
        // Get the texture details
		D3D10_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

        // Create a shader resource view of the texture
		D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		ZeroMemory(&SRVDesc, sizeof(SRVDesc));
		SRVDesc.Format = desc.Format;
		SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = desc.MipLevels;
			
		pD3DDevice->CreateShaderResourceView(texture, &SRVDesc, resourceView);
	}
}
