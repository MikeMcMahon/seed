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
} // Initiate Default Blend


/* eof */