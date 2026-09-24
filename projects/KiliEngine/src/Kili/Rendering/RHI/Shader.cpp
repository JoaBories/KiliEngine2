#include "klpch.h"
#include "Shader.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlShader.h"

//ADDAPI
Kili::Shader* Kili::Shader::create(const std::string& name, const std::string& path)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlShader(name, path); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}
