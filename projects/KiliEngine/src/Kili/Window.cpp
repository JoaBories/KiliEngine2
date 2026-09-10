#include "klpch.h"
#include "Window.h"

#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlContext.h"

bool Kili::Window::init()
{    
    if (mMsaa) GraphicContext::setMsaa(mMsaa);
    
    int windowFlags = 0;
    if (mFlags & WindowFullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN;
    if (mFlags & WindowBorderless) windowFlags |= SDL_WINDOW_BORDERLESS;
    if (mFlags & WindowResizable) windowFlags |= SDL_WINDOW_RESIZABLE;
    if (mFlags & WindowAlwaysOnTop) windowFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
    windowFlags |= GraphicContext::getWindowFlag();
    
    mWindow = SDL_CreateWindow(mTitle.c_str(), static_cast<int>(mWidth), static_cast<int>(mHeight), windowFlags);
    if (!mWindow) return false;
    
    mContext = GraphicContext::create(mWindow);
    if (!mContext) return false;
    
    setVsync(mVsync);
    
    return true;
}

void Kili::Window::update()
{
    mContext->swapBuffers();
}

void Kili::Window::close()
{
    delete mContext;
    mContext = nullptr;
    
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

Kili::Window::Window(std::string title, const WindowParameters params) :
    mTitle(std::move(title)), 
    mWindow(nullptr), mContext(nullptr),
    mWidth(params.width), mHeight(params.height), 
    mFlags(params.flags), mMsaa(params.msaa), mVsync(params.vsync)
{
}

Kili::Window::~Window()
{
    close();
}

void Kili::Window::setVsync(const bool vsync)
{
    mVsync = vsync;
    mContext->setVsync(mVsync);
}