#pragma once

namespace Sprites { 
    struct Color { 
            float r;
            float g;
            float b;
            float a;
            Color ( void ) { }
            Color ( float r, float g, float b, float a ) { 
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
#ifdef RENDER_ENG_DX
	    operator D3DXCOLOR() {
		    return D3DXCOLOR(this->r, this->g, this->b, this->a);
	    }
#else
// Opengl color struct, not supported yet, is there one?
#endif
};}