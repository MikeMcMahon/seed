#pragma once

namespace Sprites { 
	struct Type { enum type { 
		base,
		character,
		npc,
		tile,
		font,
		map,
		background
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
    struct Sprite { 
		std::string		name;
		std::string		resource;
		Type::type		kindOf;
		Position		position;
		Size			size;
		Animation		animation;
		Move			moveDistance;
		bool			canAnimate;
		bool			isVisible;
		bool			canMove;
        bool            textureLoaded;
	};

	const struct Position	DefaultPosition		= { 0, 0, 0 };
	const struct Size		DefaultSize			= { 0, 0 };
	const struct Animation	DefaultAnimation	= { 0, 0, 1, 0 };
	const struct Move		DefaultMove			= { 0, 0, 0, 0 };
	const struct Sprite		DefaultSprite		= { "", "", Type::base, DefaultPosition, DefaultSize, DefaultAnimation, DefaultMove, false, false , false, false };
}