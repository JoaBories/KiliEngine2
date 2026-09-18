#pragma once
#include "Kili/Rendering/RHI/Texture.h"

namespace Kili
{
    int WrapModeToOpenGl(const WrapMode& wrapMode);
    int FilterModeToOpenGl(const TextureFilterMethod& filterMode, bool useMipMap);
    int ImageFormatToOpenGl(const ImageFormat& format, bool data);
    
    class OpenGlTexture : public Texture
    {
    private:
        std::string mPath;
        int mWidth, mHeight;
        uint32_t mId;
        TextureParameter mParameter;
        ImageFormat mImageFormat;
    
    public:
        explicit OpenGlTexture(const TextureParameter& parameter);
        explicit OpenGlTexture(const TextureParameter& textureParameter, std::string path);
        
        bool load() override;
        bool unload() override;
        
        void use(uint8_t index = 0) override;
        void setData(void* data, uint32_t dataSize) override;
        
        [[nodiscard]] std::string getPath() const override { return mPath; }
        
        void setSize(const int width, const int height) override { mWidth = width; mHeight = height; }
        void setFormat(const ImageFormat format) override { mImageFormat = format; }
        
        void getSize(int& width, int& height) const override { width = mWidth; height = mHeight; }
        [[nodiscard]] uint32_t getWidth() const override { return mWidth; }
        [[nodiscard]] uint32_t getHeight() const override { return mHeight; }
    };
}