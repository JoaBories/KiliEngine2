#include "klpch.h"
#include "Texture.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

// ADDAPI
namespace Kili
{
    std::unique_ptr<Texture> Texture::create(const TextureParameter& textureParameter, const std::string& path)
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlTexture>(textureParameter, path); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }

    uint8_t* Texture::loadTextureFromFile(const std::string& path, int& widthOut, int& heightOut, ImageFormat& formatOut)
    {
        stbi_set_flip_vertically_on_load(true);
    
        int channels;
        uint8_t* data = stbi_load(path.c_str(), &widthOut, &heightOut, &channels, 0);
        formatOut = static_cast<ImageFormat>(channels);
        return data;
    }
}