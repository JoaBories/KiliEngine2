#include "klpch.h"
#include "OpenGlTexture.h"

#include "Kili/Core/Logger/Log.h"
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
    
    LOG_WARNING("Unknown image format");
    return GL_RGB;
}

Kili::OpenGlTexture::OpenGlTexture(const TextureParameter& textureParameter, std::string path) :
    mPath(std::move(path)), mParameter(textureParameter)
{
    unsigned char* data = loadTextureFromFile(mPath, mWidth, mHeight, mImageFormat);
    
    if (!data)
    {
        LOG_WARNING("Image load error, maybe bad texture path"); 
        mId = 0; 
        return;
    }
    
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);

    glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, FilterModeToOpenGl(mParameter.filterMode, mParameter.useMipMap));
    glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, FilterModeToOpenGl(mParameter.filterMode, false)); // As mip map don't work for upscaling

    glTextureParameteri(mId, GL_TEXTURE_WRAP_S, WrapModeToOpenGl(mParameter.wrapMode));
    glTextureParameteri(mId, GL_TEXTURE_WRAP_T, WrapModeToOpenGl(mParameter.wrapMode));
    
    glTexImage2D(
        GL_TEXTURE_2D, 0, 
        ImageFormatToOpenGl(mImageFormat, false), 
        mWidth, mHeight, 0, 
        ImageFormatToOpenGl(mImageFormat, true), GL_UNSIGNED_BYTE, 
        data);
    
    stbi_image_free(data);
    
    if (mParameter.useMipMap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    LOG_LOADING("Successfully loaded Texture " + mPath);
}

Kili::OpenGlTexture::~OpenGlTexture()
{
    glDeleteTextures(1, &mId);
    mId = 0;
}

void Kili::OpenGlTexture::use(const uint8_t index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mId);
}
