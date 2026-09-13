#pragma once
#include "Kili/Renderer/RenderCommand.h"

//ADDAPI
namespace Kili
{
    class Renderer
    {        
    public:
        static RendererApi::GraphicApi getApi() { return RendererApi::getApi(); }
        static std::string getApiName() { return toString(RendererApi::getApi()); }
        
        static void beginScene();
        static void endScene();
        
        static void submit(const std::shared_ptr<VertexArray>& vertexArray);
        
    };
}
