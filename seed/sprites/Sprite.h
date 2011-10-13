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
		int startFrame;
		int numFrames;
		float animDuration;
	};
	struct Sprite { 
		wchar_t*	name;
		wchar_t*	resource;
		Type		kindOf;
		Position	position;
		Size		size;
		Animation	animation;
	};
}