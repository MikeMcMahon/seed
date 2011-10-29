#pragma once

#include "IAnimation.h"

namespace Sprites { 
    class FrameAnimation : public IAnimation { 
    private:
        int curFrameAnimate;
    public:
        FrameAnimation(void) { 
            this->curFrameAnimate = 0;   
        }
        ~FrameAnimation(void) { }

		int CurFrame() { 
            return this->curFrameAnimate; 
        }
		
		void SetFrame(int frame) { 
			this->curFrameAnimate = frame;
		}

        void IncrementFrame() { 
	        if (this->curSkip <= this->skipFrames && this->curSkip == 0) { 
                // If there are still available frames to animate
                if (this->curFrameAnimate < this->numFrames)
		            this->curFrameAnimate++; 

                // If there are no more frames to animate
				if (this->curFrameAnimate >= this->numFrames)
                    this->curFrameAnimate = 0;
	        }
	        if (this->curSkip >= this->skipFrames) {
		        this->curSkip = 0;
		        return;
	        }
	        this->curSkip++; 
        }

        void LoopAnimation(bool loop) { 
            this->loop = loop;
        }
    }; // FrameAnimation
}
/* eof */