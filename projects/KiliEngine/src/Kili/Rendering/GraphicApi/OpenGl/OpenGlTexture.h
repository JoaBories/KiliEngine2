#pragma once
#include "Kili/Rendering/RHI/Texture.h"

namespace Kili
{
    class OpenGlTexture : public Texture
    {
    private:
        uint32_t mId;
        uint32_t mWidth, mHeight;
        std::string mPath;
    
    public:
        explicit OpenGlTexture(const TextureParameter& parameter);
        explicit OpenGlTexture(std::string path);
        
        bool load() override;
        bool unload() override;
        
        void use() override;
        void setData(void* data, const uint32_t size) override;
        
        [[nodiscard]] std::string getPath() const override { return mPath; }
        uint32_t getWidth() override { return mWidth; }
        uint32_t getHeight() override { return mHeight; }
    };
}