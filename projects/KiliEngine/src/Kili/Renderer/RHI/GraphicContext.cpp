#include "klpch.h"
#include "GraphicContext.h"

#include "Kili/Renderer/Renderer.h"
#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlContext.h"
#include "Kili/Core/Logger/Log.h"

//ADDAPI
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
