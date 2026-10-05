#pragma once

#include "SDL.h"

namespace Kili
{
    class GraphicContext
    {
    public:
        virtual ~GraphicContext() = default;
        
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void swapBuffers() = 0;
        
        static std::unique_ptr<GraphicContext> create(SDL_Window* windowHandle);
    };
}