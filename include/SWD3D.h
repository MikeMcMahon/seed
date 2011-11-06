#pragma once

#include "SWIRenderer.h"

namespace Renderers {
	class D3DRend : public IRenderer { 
	public:
		D3DRend ( void );

		bool StartupInterface ( HWND hWnd, int width, int height );
		void ShutdownInterface ( void );
		
		ID3D10Device* GetDevice ( void );

	private:
		void InitiateDefaultBlend ( D3D10_BLEND_DESC * );
		
	}; // D3DRend
} 