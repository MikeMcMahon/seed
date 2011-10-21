#pragma once

#include "..\animations\FrameAnimation.h"
#include "SpriteType.h"
#include "Size.h"
#include "Position.h"
#include "Move.h"

namespace Sprites {
    class ISprite { 
    protected:
        wchar_t         name[100];
        bool            textureLoaded;
        Position        position;
        Size            size;
        Move            move;
        Type::type      kindOf;
    public:
		virtual void SpriteType(Type::type kindOf) = 0;
		virtual Type::type SpriteType() = 0;

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