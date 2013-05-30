#pragma once

#include "SWIRenderer.h"

namespace Renderers {
	class DXRend : public IRenderer { 
	public:
		DXRend ( void );

		bool StartupInterface ( HWND hWnd, int width, int height );
		void ShutdownInterface ( void );
		void Render ( void );
		
		ID3D10Device* GetDevice ( void );

	private:
		void InitiateDefaultBlend ( D3D10_BLEND_DESC * );
		
	}; // D3DRend
} 