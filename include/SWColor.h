#pragma once

#define SW_BLACK Util::SWColor(0.0f, 0.0f, 0.0f, 1.0f)
#define SW_WHITE Util::SWColor(1.0f, 1.0f, 1.0f, 1.0f)

namespace Util { 
	typedef struct _SWColor { 
        float r;
        float g;
        float b;
        float a;
        _SWColor ( void ) { }
        _SWColor ( float r, float g, float b, float a ) { 
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
#ifdef RENDER_ENG_DX
	    operator D3DXCOLOR() {
		    return D3DXCOLOR(this->r, this->g, this->b, this->a);
	    }
#elif defined(RENDER_ENGINE_GL)
		// Opengl color struct, not supported yet, is there one?
#endif
	} SWColor; // Color
} // Sprites