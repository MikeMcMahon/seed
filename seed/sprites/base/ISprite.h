#pragma once

#include "FrameAnimation.h"

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
	struct Move { 
        bool canMove;
		float
			up,
			down,
			left,
			right;
	};
    class ISprite { 
    protected:
        wchar_t         name[100];
        wchar_t         resource[100];
        bool            isVisible;
        bool            textureLoaded;
        Position        position;
        Size            size;
        Move            move;
    public:
        Type::type      kindOf;
        void CanMove(bool canMove) { this->move.canMove = canMove; }
        bool CanMove() { return this->move.canMove; }

        void Name(wchar_t* name) { wcscpy_s ( this->name, name ); }
        const wchar_t* Name() { return this->name; }

        void Resource(wchar_t* resource) { wcscpy_s ( this->resource, resource ); }
        const wchar_t* Resource() { return this->resource; };

        void IsVisible(bool visible) { this->isVisible = visible; }
        bool IsVisible() { return this->isVisible; };

        void TextureLoaded(bool loaded) { this->textureLoaded = loaded; }
        bool TextureLoaded() { return this->textureLoaded; };

        Move MoveDistance() { return move; };
        virtual void MoveDistance(float up, float down, float left, float right) { 
            this->move.up = up;
            this->move.left = left;
            this->move.right = right;
            this->move.down = down;
        }

        virtual Position Position() { return position; }
        virtual void Position(float x, float y, float z) {
            position.x = x;
            position.y = y;
            position.z = z;
        }

        virtual Size Size() { return size; }
        virtual void Size(float height, float width) { 
            size.height = height;
            size.width = width;
        }
    }; // ISprite
}