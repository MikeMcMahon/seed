/*#pragma once

namespace Sprites { 
	struct Type { enum type { 
		base,
		character,
		battlecharacter,
		monster,
		npc,
		tile,
		font,
		map,
		background,
		color
	};};
	struct Position { 
		float 
			x, 
			y, 
			z;
	};
	struct Size { 
		float 
			height, 
			width;
	};
	struct Animation {
        int curSkip;
        int curFrameAnimate;
        float skipFrames;
		int curFrame;
		int startFrame;
		int numFrames;
		float animDuration;
	};
	struct Move { 
		float
			up,
			down,
			left,
			right;
	};
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
        };

    // Allows the user to specify if they would like the sprite to fade between colors or alphas or both
    // TODO - Implement fade
    struct Fade { 
        bool doFade;
        Color startColor;
        Color endColor;
        float durationInMili;
    };

    // Allows the user to specify the sprite should scale in or out 
    struct Scale {
        float y;            // 1.0f = 100%
        float x;
    };

    struct Sprite { 
		wchar_t		name[100];
		wchar_t		resource[100];
		Type::type	kindOf;
		Position	position;
		Size		size;
		Animation	animation;
		Move		moveDistance;
        Color       color;
        Scale       scale;
		bool		canAnimate;
		bool		isVisible;
		bool		canMove;
        bool        textureLoaded;
	};

    const struct Color      DefaultColor        = { 1.0f, 1.0f, 1.0f, 1.0f};
    const struct Fade       DefaultFade         = { false, DefaultColor, DefaultColor, 0 };
    const struct Scale      DefaultScale        = { 1.0f, 1.0f };                      
	const struct Position	DefaultPosition		= { 0, 0, 0 };
	const struct Size		DefaultSize			= { 0, 0 };
	const struct Animation	DefaultAnimation	= { 0, 0, 1, 0 };
	const struct Move		DefaultMove			= { 0, 0, 0, 0 };
	const struct Sprite		DefaultSprite		= { L"", 
                                                    L"", 
                                                    Type::base, 
                                                    DefaultPosition, 
                                                    DefaultSize, 
                                                    DefaultAnimation, 
                                                    DefaultMove, 
                                                    DefaultColor,
                                                    DefaultScale,
                                                    false, false , 
                                                    false, false };
}*/