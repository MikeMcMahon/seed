#pragma once

/// NOTE ///////////////////////////////////////////////
/// The render engine must be set in here and then
/// recompiled for the specific engine the users wishes 
/// to use
////////////////////////////////////////////////////////
#define RENDER_ENG_DX // Render for the DX System
// #define RENDER_ENG_GL // not supported yet 

// Required for rendering stuff on time
#ifndef TICKS_PER_SECOND
	#define TICKS_PER_SECOND 60
#endif

#define SKIP_TICKS (1000.0f / (float)TICKS_PER_SECOND)

#ifndef MAX_FRAMESKIP
	#define MAX_FRAMESKIP 5
#endif

// Sprite calcs
#ifndef MAX_SPRITES
	#define MAX_SPRITES			2048
#endif
#define NUM_POOL_SPRITES	MAX_SPRITES

// Window handling stuff
// TODO put these somewhere else, not in a define 
#ifndef WINDOW_WIDTH
	#define WINDOW_WIDTH 1024
#endif 
#ifndef WINDOW_HEIGHT
	#define WINDOW_HEIGHT 768
#endif

#ifndef CLASS_NAME
	#define CLASS_NAME TEXT("DEFAULT")
#endif

#include "SWColor.h"
#include "SWCoordinates.h"
#include "SWMove.h" 
#include "SWScale.h"
#include "SWSize.h"
#include "SWIRenderer.h"

#ifdef RENDER_ENG_DX 
#include "SWD3D.h"
#endif

typedef struct _WindowOffsets { 
    float offsetTop;
    float offsetRight;
    float offsetBottom;
    float offsetLeft;
} WindowOffsets;

namespace SW2D { 

class SWDevice { 
private:
	HWND hWnd;
protected:
	Renderers::IRenderer* renderer;
	Util::SWSizeI windowDimensions;
public:
	/// Creates a game window with the given size 
	/// Returns a handle to the created window
	/// If DX is the engine, will initialize the DX system and attach it to the window 
	bool CreateGameWindow ( HINSTANCE hInstance, int width, int height);
	HWND* GetWindowHandle ( void );
	bool InitInterface ( void );
	Renderers::IRenderer* GetRenderer ( void );

}; // SWDevice

} // Engine

namespace Timers { 
    class GameClock
    {
    public:
        static GameClock* GetInstance();
        void Initialize ( void );
        DWORD timeCount;

        void GetTime ( LONGLONG* t );
        LONGLONG GetTimeElapsed ( void );
        LONGLONG frequency; 

        ~GameClock(void);
    protected:
        GameClock(void);

    private:
        static GameClock* pInstance;
    }; // GameClock
} // Timers

namespace TextureUtils { 

    class TextureHandler { 
    public:
        static ID3D10Texture2D* GetTexture2DFromFile(LPCWSTR, ID3D10Device*);
        static void GetResourceViewFromTexture(ID3D10Texture2D*, ID3D10ShaderResourceView**, ID3D10Device*);

    }; // TextureHandler
} // TextureUtils

namespace Font {
	enum FontSize { 
		Tiny = 10,
		Normal = 20,
		Large = 30,
		Huge = 40
	};

	class FontHandler { 
	public: 
		bool InitFont();
		void DrawTextNow(float x, float y, LPCWSTR text, Util::SWColor color = SW_BLACK);
		void FontRect(RECT* rect, float x, float y);
	};
} // Font
