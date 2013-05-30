#pragma once

#include "ISprite.h"

namespace Renderers { 
class IRenderer { 
public: 
	virtual bool StartupInterface ( HWND hWnd, int width, int height ) = 0;
	virtual void ShutdownInterface ( void ) = 0;
	virtual void Render ( void ) = 0;
};
}