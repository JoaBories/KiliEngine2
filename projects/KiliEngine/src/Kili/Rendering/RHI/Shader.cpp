#include "klpch.h"
#include "Shader.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlShader.h"

//ADDAPI
namespace Kili
{
    std::unique_ptr<Shader> Shader::create(const std::string& path)
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlShader>(path); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }
}