#include "klpch.h"
#include "OpenGlContext.h"

#include "Kili/Logger/Log.h"

void Kili::OpenGlContext::init(SDL_Window* windowHandle)
{
    mWindowHandle = windowHandle;
    
    // OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    
    // 8 bits color buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    mContext = SDL_GL_CreateContext(mWindowHandle);
    
    const int version = gladLoadGL(SDL_GL_GetProcAddress);
    if (!version) LOG_ERROR("OpenGL could not initialize");
    else LOG_LOADING("OpenGl initialized");

    const std::string openglVersion = std::to_string(GLAD_VERSION_MAJOR(version)) + "." + std::to_string(GLAD_VERSION_MINOR(version));
    const std::string glslVersion = std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    
    LOG_LOADING("OpenGL " + openglVersion + " with GLSL " + glslVersion);
    LOG_LOADING("Running on : " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
}

void Kili::OpenGlContext::close()
{
    SDL_GL_DestroyContext(mContext);
}

void Kili::OpenGlContext::setMsaa(const int samples)
{
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);
}