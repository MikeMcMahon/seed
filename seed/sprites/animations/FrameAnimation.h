#pragma once

#include "IAnimation.h"
#include "../../util/GameClock.h"

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
            LONGLONG currentFrameTime; 
            if (this->lastFrameTime == 0) { 
                GameUtil::GameClock::GetInstance()->GetTime ( &this->lastFrameTime ); 
                currentFrameTime = this->lastFrameTime;
            } else { 
                GameUtil::GameClock::GetInstance()->GetTime ( &currentFrameTime ); 
            }

            LONGLONG freq = GameUtil::GameClock::GetInstance()->frequency;
            LONGLONG frameDiff = ( currentFrameTime - this->lastFrameTime ) / GameUtil::GameClock::GetInstance()->frequency;
            if ( frameDiff >= this->elapseFrame ) { 

                if (this->curFrameAnimate < this->numFrames) { 
		            this->curFrameAnimate++; 
                }

                // If there are no more frames to animate
				if (this->curFrameAnimate >= this->numFrames)
                    this->curFrameAnimate = 0;

                GameUtil::GameClock::GetInstance()->GetTime ( &this->lastFrameTime );
                // OutputDebugString ( L"Incremeting frame on time\n" );
            }
            
            /*
	        if (this->curSkip <= this->skipFrames && this->curSkip == 0) { 
                // If there are still available frames to animate
                if (this->curFrameAnimate < this->numFrames) { 
		            this->curFrameAnimate++; 
                    OutputDebugString ( L"Incrementing frame on skip\n");
                }

                // If there are no more frames to animate
				if (this->curFrameAnimate >= this->numFrames)
                    this->curFrameAnimate = 0;
	        }
	        if (this->curSkip >= this->skipFrames) {
		        this->curSkip = 0;
		        return;
	        }
	        this->curSkip++; */
        }

        void LoopAnimation(bool loop) { 
            this->loop = loop;
        }
    }; // FrameAnimation
}
/* eof */