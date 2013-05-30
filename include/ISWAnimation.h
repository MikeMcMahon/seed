#pragma once

namespace Sprites { 
    class IAnimation { 
    protected:
        int numFrames;
        bool loop;
        float elapseFrame;
        LONGLONG lastFrameTime;
    public:
        int NumFrames() { 
            return this->numFrames; 
        } 
        virtual void AnimationDetail(float duration, int numFrames) {
            this->elapseFrame = ( (TICKS_PER_SECOND * duration) / (float)numFrames ) * ( ( 1000.0f / (float)TICKS_PER_SECOND ) );
            this->lastFrameTime = 0;
            this->numFrames = numFrames;
        }
        virtual bool LoopAnimation() { return loop; }
        virtual void LoopAnimation(bool loop) { this->loop = loop; }

        virtual void IncrementFrame() { return; } 
    }; //IAnimation
}
/* eof */