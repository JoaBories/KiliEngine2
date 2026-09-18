#pragma once
#include "Kili/AssetManager/Asset.h"
#include "Kili/Core/Logger/Log.h"

namespace Kili
{    
    // R -> Red, RA -> Red Alpha, RGB -> Red Green Blue, RGBA -> Red Green Blue Alpha
    enum class ImageFormat : uint8_t
    {
        R = 1, RA = 2, RGB = 3, RGBA = 4
    };

    enum class WrapMode : uint8_t
    {
        Repeat, Mirrored, ClampToEdge
    };
    
    enum class TextureFilterMethod : uint8_t
    {
        Nearest, Linear
    };
    
    struct TextureParameter
    {
        bool useMipMap;
        WrapMode wrapMode;
        TextureFilterMethod filterMode;

        TextureParameter(const bool useMipMap, const WrapMode wrapMode, const TextureFilterMethod filterMode) :
            useMipMap(useMipMap), wrapMode(wrapMode), filterMode(filterMode)
        {
        }
        
        TextureParameter() = default;
    };
    
    /**
     * Texture, derived form IAsset. Abstract texture from different Graphic Api.
     * You can use it to fetch (through the constructor) textures from files and load/unload them later.
     * This will be mainly used by the Asset Manager.
     * You can also use it for loading texture during runtime following this but note that this will certainly 
     * be abstracted in another way later.
     *      - Constructor with parameter (wrap, filtering and mipmap).
     *      - setSize() giving width and height.
     *      - load() creating Texture on gpu.
     *      - setData() uploading information to gpu.
     */
    class Texture : public IAsset
    {
    public:
        virtual void use(uint8_t index = 0) = 0;
        virtual void setData(void* data, uint32_t dataSize) = 0;
        
        /** Only for texture loaded from file. Return "" if created in runtime. **/
        [[nodiscard]] virtual std::string getPath() const = 0;
        
        /** Only for runtime generated textures. Need to use before texture->load() **/
        virtual void setSize(int width, int height) = 0;
        /** Only for runtime generated textures. Need to use before texture->load() **/
        virtual void setFormat(ImageFormat format) = 0;
        
        virtual void getSize(int& width, int& height) const = 0;
        [[nodiscard]] virtual uint32_t getWidth() const = 0;
        [[nodiscard]] virtual uint32_t getHeight() const = 0;
        
        static Texture* create(const TextureParameter& textureParameter);
        static Texture* create(const TextureParameter& textureParameter, std::string path);
        
        static uint8_t* loadTextureFromFile(const std::string& path, int& widthOut, int& heightOut, ImageFormat& formatOut);
    };
}
