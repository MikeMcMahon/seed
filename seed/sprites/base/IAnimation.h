#pragma once

namespace Sprites { 
    class IAnimation { 
    protected:
        int curSkip;
        int numFrames;
        float skipFrames;
        bool loop;
    public:
        int NumFrames() { 
            return this->numFrames; 
        } 
        virtual void AnimationDetail(float duration, int numFrames) {
            if (numFrames <= 0)
                this->skipFrames = 0;   // Run in continuous mode
            else 
                this->skipFrames = (TICKS_PER_SECOND * duration) / (float)numFrames;
            this->curSkip = 0;
            this->numFrames = numFrames;
        }
        virtual bool LoopAnimation() { return loop; }
        virtual void LoopAnimation(bool loop) { this->loop = loop; }

        virtual void IncrementFrame() { return; } 
    }; //IAnimation
}
/* eof */