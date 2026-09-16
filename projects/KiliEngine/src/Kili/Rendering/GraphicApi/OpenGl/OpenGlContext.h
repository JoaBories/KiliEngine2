#pragma once
#include "Kili/Rendering/RHI/GraphicContext.h"

namespace Kili
{
    class OpenGlContext : public GraphicContext
    {
    private:
        SDL_Window* mWindowHandle;
        SDL_GLContext mContext;
        
    public:
        OpenGlContext(SDL_Window* windowHandle);
        
        void init() override;
        void close() override;
        
        void swapBuffers() override { SDL_GL_SwapWindow(mWindowHandle); }
    };
}
