#include "klpch.h"
#include "GraphicContext.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlContext.h"
#include "Kili/Core/Logger/Log.h"

//ADDAPI
namespace Kili
{
    std::unique_ptr<GraphicContext> GraphicContext::create(SDL_Window* windowHandle)
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlContext>(windowHandle); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }
}