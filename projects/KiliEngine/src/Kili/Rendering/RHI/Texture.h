#pragma once
#include "Kili/AssetManager/Asset.h"
#include "Kili/Core/Logger/Log.h"

namespace Kili
{    
    // G -> Grey, GA -> Grey Alpha, RGB -> Red Green Blue, RGBA -> Red Green Blue Alpha
    enum class ImageFormat : uint8_t
    {
        G, GA, RGB, RGBA
    };

    enum class WrapMode : uint8_t
    {
        Repeat, Mirrored, ClampToEdge
    };
    
    enum class FilterMode : uint8_t
    {
        Nearest, Linear
    };
    
    struct TextureParameter
    {
        ImageFormat imageFormat;
        uint32_t width, height;
        
        bool useMipMap;
        WrapMode wrapMode;
        FilterMode filterMode;
        
        TextureParameter(const ImageFormat image, const int width, const int height,
            const bool useMipMap = false, const WrapMode wrapMode = WrapMode::Repeat, const FilterMode filterMode = FilterMode::Linear) :
            imageFormat(image), width(width), height(height), useMipMap(useMipMap), wrapMode(wrapMode), filterMode(filterMode) 
        {}
    };
    
    class Texture : public IAsset
    {
    public:
        virtual void use() = 0;
        virtual void setData(void* data, const uint32_t size) = 0;
        
        /** Only for texture loaded from file. Return "" if none **/
        [[nodiscard]] virtual std::string getPath() const = 0;
        
        virtual uint32_t getWidth() = 0;
        virtual uint32_t getHeight() = 0;
        
        static Texture* create(const TextureParameter& textureParameter);
        static Texture* create(std::string path);
    };
}
