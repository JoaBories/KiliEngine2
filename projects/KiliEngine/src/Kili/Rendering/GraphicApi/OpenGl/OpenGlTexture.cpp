#include "klpch.h"
#include "OpenGlTexture.h"

#include "Vendor/stb_image.h"

int Kili::WrapModeToOpenGl(const WrapMode& wrapMode)
{
    switch (wrapMode)
    {
        case WrapMode::Repeat : return GL_REPEAT; break;
        case WrapMode::Mirrored : return GL_MIRRORED_REPEAT; break;
        case WrapMode::ClampToEdge : return GL_CLAMP_TO_EDGE; break;
    }
    
    LOG_WARNING("Unknown wrap mode");
    return GL_REPEAT;
}

int Kili::FilterModeToOpenGl(const TextureFilterMethod& filterMode, const bool useMipMap)
{
    switch (filterMode)
    {
        case TextureFilterMethod::Linear : return useMipMap ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR; break;
        case TextureFilterMethod::Nearest : return useMipMap ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST; break;
    }
    
    LOG_WARNING("Unknown texture filter mode");
    return GL_LINEAR;
}

int Kili::ImageFormatToOpenGl(const ImageFormat& format, const bool data)
{
    switch (format)
    {
        case ImageFormat::R : return data ? GL_RED : GL_R8; break;
        case ImageFormat::RA : return data ? GL_RG : GL_RG8; break;
        case ImageFormat::RGB : return data ? GL_RGB : GL_RGB8; break;
        case ImageFormat::RGBA : return data ? GL_RGBA : GL_RGBA8; break;
    }
}

Kili::OpenGlTexture::OpenGlTexture(const TextureParameter& parameter) :
    mId(0), mParameter(parameter)
{
}

Kili::OpenGlTexture::OpenGlTexture(const TextureParameter& textureParameter, std::string path) :
    mPath(std::move(path)), mId(0), mParameter(textureParameter)
{
}

bool Kili::OpenGlTexture::load()
{
    if (mPath.empty() && mWidth == 0 && mHeight == 0)
    {
        LOG_WARNING("Attempt to load a texture without path or parameters");
        return false;
    }
    
    unsigned char* data = nullptr;
    
    if (!mPath.empty())
    {
        int width, height;
        ImageFormat imageFormat;
        data = Texture::loadTextureFromFile(mPath, width, height, imageFormat);
        
        mWidth = width;
        mHeight = height;
        mImageFormat = imageFormat;
    }
    
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);

    glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, FilterModeToOpenGl(mParameter.filterMode, mParameter.useMipMap));
    glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, FilterModeToOpenGl(mParameter.filterMode, false)); // As mip map don't work for upscaling

    glTextureParameteri(mId, GL_TEXTURE_WRAP_S, WrapModeToOpenGl(mParameter.wrapMode));
    glTextureParameteri(mId, GL_TEXTURE_WRAP_T, WrapModeToOpenGl(mParameter.wrapMode));
    
    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, 
            ImageFormatToOpenGl(mImageFormat, false), 
            mWidth, mHeight, 0, 
            ImageFormatToOpenGl(mImageFormat, true), GL_UNSIGNED_BYTE, 
            data);
        
        if (mParameter.useMipMap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        
        stbi_image_free(data);
    }
    
    mLoaded = true;
    return true;
}

bool Kili::OpenGlTexture::unload()
{
    glDeleteTextures(1, &mId);
    mId = 0;
    
    mLoaded = false;
    return true;
}

void Kili::OpenGlTexture::use(const uint8_t index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mId);
}

void Kili::OpenGlTexture::setData(void* data, const uint32_t dataSize)
{
    if (const uint32_t expectedSize = mWidth * mHeight * static_cast<uint8_t>(mImageFormat); 
        dataSize != expectedSize)
    {
        LOG_WARNING("Data size mismatch texture parameters height width and channels : " + std::to_string(expectedSize) + " expected, " + std::to_string(dataSize) + " given");
    }
    
    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D, 0, 
            ImageFormatToOpenGl(mImageFormat, false), 
            mWidth, mHeight, 0, 
            ImageFormatToOpenGl(mImageFormat, true), GL_UNSIGNED_BYTE, 
            data);
        
        if (mParameter.useMipMap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        LOG_WARNING("Data pointer is null");
    }
}
