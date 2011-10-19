#pragma once

namespace Sprites { 
    struct Color { 
            float r;
            float g;
            float b;
            float a;
#ifdef RENDER_ENG_DX
	    operator D3DXCOLOR() {
		    return D3DXCOLOR(r, g, b, a);
	    }
#else
// Opengl color struct, not supported yet, is there one?
#endif
    };}