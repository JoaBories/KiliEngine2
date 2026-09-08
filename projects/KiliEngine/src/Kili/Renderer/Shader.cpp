#include "klpch.h"
#include "Shader.h"

#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlShader.h"

Kili::Shader* Kili::Shader::create(const std::string& name, const std::vector<std::string>& paths)
{
    switch (GRAPHIC_API)
    {
        case GraphicApi::OpenGl : return new OpenGlShader(name, paths); break;
        default: return nullptr;
    }
    
    //ADDAPI
}
