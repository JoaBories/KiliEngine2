#pragma once
#include "VertexArray.h"


namespace Kili
{    
    class RendererApi
    {
    public:
        enum class GraphicApi : char
        {
            None = 0,
            OpenGl = 1,
        };
        
        virtual ~RendererApi() = default;
        
        virtual void clear(const Vector4& clearColor) = 0;
        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        
        [[nodiscard]] static GraphicApi getApi() { return mGraphicApi; }
        
    private:
        static GraphicApi mGraphicApi;
    
    };
    
    inline std::string toString(const RendererApi::GraphicApi e)
    {
        switch (e)
        {
            case RendererApi::GraphicApi::None: return "None";
            case RendererApi::GraphicApi::OpenGl: return "OpenGl";
        }
        
        return "Unknown";
    }
}