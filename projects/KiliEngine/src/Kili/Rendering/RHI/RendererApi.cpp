#include "klpch.h"
#include "RendererApi.h"

#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlRendererApi.h"

Kili::GraphicApi Kili::RendererApi::mApi = GraphicApi::OpenGl;

Kili::RendererApi* Kili::RendererApi::create()
{
    switch (mApi)
    {
        case GraphicApi::OpenGl : return new OpenGlRendererApi; break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + toString(mApi));
    return nullptr;
}