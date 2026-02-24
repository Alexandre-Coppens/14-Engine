#include "Time.h"

#include <algorithm>
#include <SDL_timer.h>

unsigned int Time::u16FrameStart = 0;
unsigned int Time::u16FrameTime = 0;
unsigned int Time::u16LastFrame = 0;
float Time::deltaTime = 0;
float Time::currentFrameTime = 0;

unsigned int Time::ComputeDeltaTime()
{
    u16FrameStart = SDL_GetTicks();
    unsigned int dt = u16FrameStart - u16LastFrame;
    u16LastFrame = u16FrameStart;
    currentFrameTime = static_cast<float>(u16FrameStart);
    dt = std::min(dt, MAX_DT);
    deltaTime = static_cast<float>(dt) / 1000.0f;
    return dt;
}

void Time::DelayTime()
{
    u16FrameTime = SDL_GetTicks() - u16FrameStart;
    if (u16FrameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - u16FrameTime);
    }
}