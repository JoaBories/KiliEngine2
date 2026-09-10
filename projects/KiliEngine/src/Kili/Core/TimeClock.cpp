#include "klpch.h"
#include "TimeClock.h"

#include "Kili/Core/Logger/Log.h"

const unsigned long long Kili::TimeClock::SdlFrequency = SDL_GetPerformanceFrequency();

unsigned long long Kili::TimeClock::mTime = 0;
unsigned int Kili::TimeClock::mFrameCount = 0;
        
float Kili::TimeClock::mDeltaTime = 0.0f;

Kili::TimeClock::TimeClock(const unsigned int maxFps, const float maxDeltaTime) : 
    mFrameStart(0), mFrameTime(0), mLastFrameStart(0),
    mMaxFps(maxFps),
    mMaxDeltaTime(maxDeltaTime),
    mLogging(false), mLogInterval(0.0f), mLastLog(0)
{
    mLastFrameStart = SDL_GetPerformanceCounter();
    mFrameStart = mLastFrameStart;
    if (mMaxFps) mTicksPerFrame = SdlFrequency / mMaxFps;
}

void Kili::TimeClock::computeTime()
{
    // Set frame timers.
    mFrameStart = SDL_GetPerformanceCounter();
    mFrameTime = mFrameStart - mLastFrameStart;
    mLastFrameStart = mFrameStart;
    
    // Compute Delta time.
    mDeltaTime = Klm::Min(static_cast<float>(mFrameTime) / static_cast<float>(SdlFrequency), mMaxDeltaTime);
    
    // Update time and frame count.
    mTime += mFrameTime;
    mFrameCount++;
    
    // LogFps if needed
    if (mLogging)
    {
        if (time() > mLastLog + mLogInterval)
        {
            LOG_INFO("Avg : " + std::to_string(1 / avgFrameTime()) + " | Current : " + std::to_string(1 / deltaTime()) + " | FrameTime : " + std::to_string(deltaTime() * 1000));
            mLastLog = time();
        }
    }
}

void Kili::TimeClock::delayTime() const
{
    if (mMaxFps == 0) return;

    if (const unsigned long long elapsed = SDL_GetPerformanceCounter() - mFrameStart; elapsed < mTicksPerFrame)
    {
        SDL_DelayPrecise((mTicksPerFrame - elapsed) * 1000000000 / SdlFrequency);
        // How many ticks remaining for this frame 
        // times 1,000,000,000 for conversion from t/s to t/ns
        // divided by Sdl frequency to convert from t/ns to ns.
    }
}