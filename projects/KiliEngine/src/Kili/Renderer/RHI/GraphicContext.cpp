#include "klpch.h"
#include "GraphicContext.h"

#include "Kili/Renderer/Renderer.h"
#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlContext.h"
#include "Kili/Core/Logger/Log.h"

//ADDAPI
void Kili::GraphicContext::setMsaa(const int samples)
{
    switch (Renderer::getApi())
    {
        case RendererApi::GraphicApi::OpenGl :
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);
            return;
            break;
        
        case RendererApi::GraphicApi::None :
            return;
            break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
}

int Kili::GraphicContext::getWindowFlag()
{
    switch (Renderer::getApi())
    {
        case RendererApi::GraphicApi::OpenGl : return SDL_WINDOW_OPENGL; break;
        case RendererApi::GraphicApi::None : return 0;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return 0;
}

Kili::GraphicContext* Kili::GraphicContext::create(SDL_Window* windowHandle)
{
    switch (Renderer::getApi())
    {
        case RendererApi::GraphicApi::OpenGl : return new OpenGlContext(windowHandle); break;
        case RendererApi::GraphicApi::None : return nullptr; break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}
