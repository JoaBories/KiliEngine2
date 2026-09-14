#pragma once

#include "Kili/Core/TimeClock.h"
#include "Kili/Window.h"
#include "Kili/Core/Logger/ConsoleLogger.h"
#include "Kili/Core/Events/Event.h"

#include "Kili/Renderer/RHI/Shader.h"
#include "Kili/Renderer/RHI/VertexArray.h"

namespace Kili
{
    class Engine
    {
    private:
        ConsoleLogger* mConsoleLogger;
        Window* mWindow;
        
        bool mIsRunning;
        bool mMinimized;
        
        bool mLoggingEvents;
        int mEventLogFilter;
        
        /**
         * Init all the engine components and set them up. \n
         * Init order :
         *  - Init console logger first, so we can see errors.
         *  - Load Engine Config from "KiliEngine.ini".
         *  - Config console logger.
         *  - Config event logging.
         *  - Init SDL3 components (only VIDEO and GAMEPAD for now).
         *  - Init and config window, window init Graphic Api context.
         *  - Init and config TimeClock.
         *  - Config SceneManager with selection of scenes.
         *  - Load the first scene.
         */
        void init();
        
        /**
         * Do an engine tick called while the engine is running. \n
         * Loop order :
         *  - Compute Time.
         *  - Poll sdl events in EventDispatcher.
         *  - Update scene.
         *  - Render if not minimized.
         *  - Reload or Load a scene if asked.
         *  - Update window (swap buffers, vsync take place here).
         *  - Delay time if fps are locked.
         */
        void loop();
        
        /**
         * Close the engine and all his components. \n
         */
        void close();
        
        void onEvent(const IEvent& event);
        void pollEvents();
        
    public:
        Engine();
        virtual ~Engine() = default;
        
        void run(); // Called by the entry point
    };
    
    // To be defined in runtime app
    Engine* CreateEngine();
}