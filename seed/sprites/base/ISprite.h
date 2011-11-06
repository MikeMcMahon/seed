#pragma once

#include "../animations/FrameAnimation.h"
#include "SpriteType.h"

namespace Sprites {
    class ISprite { 
    protected:
        wchar_t         name[100];
        bool            textureLoaded;
        Util::SWCoordinates     position;
        Util::SWSizeF            size;
        Util::SWMove            move;
        Type::type      kindOf;
    public:
		virtual void SpriteType(Type::type kindOf) = 0;
		virtual Type::type SpriteType() = 0;

        void TextureLoaded(bool loaded) { this->textureLoaded = loaded; }
        bool TextureLoaded() { return this->textureLoaded; };

        Util::SWMove MoveDistance() { return move; };
        virtual void MoveDistance(float up, float down, float left, float right) { 
            this->move.up = up;
            this->move.left = left;
            this->move.right = right;
            this->move.down = down;
        }

        virtual Util::SWCoordinates Position() { return position; }
        virtual void Position(float x, float y, float z) {
            position.x = x;
            position.y = y;
            position.z = z;
        }

        virtual Util::SWSizeF Size() { return size; }
        virtual void Size(float height, float width) { 
            size.height = height;
            size.width = width;
        }
    }; // ISprite
}