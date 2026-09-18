#pragma once

#include "Kili/Rendering/RHI/VertexArray.h"

namespace Kili
{    
    enum class GraphicApi : char
    {
        None = 0,
        OpenGl = 1,
    };
    
    inline std::string toString(const GraphicApi e)
    {
        switch (e)
        {
            case GraphicApi::None: return "None";
            case GraphicApi::OpenGl: return "OpenGl";
        }
        
        return "Unknown";
    }
    
    class RendererApi
    {
    private:
        static GraphicApi mApi;
        
    public:
        virtual ~RendererApi() = default;
        
        [[nodiscard]] static GraphicApi getApi() { return mApi; }
        [[nodiscard]] static RendererApi* create();
        
        // Draw
        virtual void draw(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        
        // Clear
        virtual void clear(const Vector4& clearColor) = 0;
        
        // Utils
        virtual void setVsync(bool enabled) = 0;
        [[nodiscard]] virtual bool isVsync() const = 0;
        
        virtual void setMsaa(int samples) const = 0;

        [[nodiscard]] virtual int getWindowFlag() const = 0;
    };
}