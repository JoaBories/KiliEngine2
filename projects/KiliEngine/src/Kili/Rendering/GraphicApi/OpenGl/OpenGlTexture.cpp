#include "klpch.h"
#include "OpenGlTexture.h"

Kili::OpenGlTexture::OpenGlTexture(const TextureParameter& parameter)
{
    
}

Kili::OpenGlTexture::OpenGlTexture(std::string path)
{
    
}

bool Kili::OpenGlTexture::load()
{
    mLoaded = true;
    return true;
}

bool Kili::OpenGlTexture::unload()
{
    mLoaded = false;
    return true;
}

void Kili::OpenGlTexture::use()
{
    glActiveTexture(mId);
}

void Kili::OpenGlTexture::setData(void* data, const uint32_t size)
{
    
}
