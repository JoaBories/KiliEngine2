#include "klpch.h"
#include "Texture.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlTexture.h"

// ADDAPI
Kili::Texture* Kili::Texture::create(const TextureParameter& textureParameter)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlTexture(textureParameter); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}

Kili::Texture* Kili::Texture::create(std::string path)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlTexture(path); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}
