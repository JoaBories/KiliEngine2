#pragma once

#include "Kili/Core/Core.h"
#include "Kili/Renderer/GraphicContext.h"

#include "SDL.h"
#include <string>

namespace Kili
{
    enum EnumWindowFlags : char
    {
        WindowFullscreen =  BIT(0),
        WindowBorderless =  BIT(1),
        WindowAlwaysOnTop = BIT(2),
        WindowResizable =   BIT(3),
    };
    
    struct WindowParameters
    {
        /** Height and Width in pixel if not fullscreen. **/
        unsigned int height, width;
        /** Flags from EnumWindowFlags. \n Example : WindowVsync | WindowFullscreen | WindowBorderless. **/
        char flags;
        /** Number of samples for MSAA antialiasing. Set to zero to deactivate. **/
        char msaa;
        /** The window should start with vsync or no **/
        bool vsync; 
    };
    
    class Window
    {
    private:
        std::string mTitle;
        SDL_Window* mWindow;
        GraphicContext* mContext;
        unsigned int mWidth, mHeight;
        char mFlags;
        char mMsaa;
        bool mVsync;
    
        
    public:
        Window(std::string title, WindowParameters params);
        ~Window();

        bool init();
        void update();
        void close();
        
        // Rule of zero
        Window(const Window& other) = delete;
        Window(Window&& other) noexcept = delete;
        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) noexcept = delete;
        
        [[nodiscard]] SDL_Window* getWindow() const { return mWindow; }
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
        
        [[nodiscard]] char getFlags() const { return mFlags; }
        
        [[nodiscard]] char getMsaa() const { return mMsaa; }
        
        [[nodiscard]] bool isVsync() const { return mVsync; }
        void setVsync(bool vsync);
    };
}
