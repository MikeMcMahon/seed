#pragma once

namespace Renderers { 
class IRenderer { 
public: 
	virtual bool StartupInterface ( HWND hWnd, int width, int height ) = 0;
	virtual void ShutdownInterface ( void ) = 0;

};
}