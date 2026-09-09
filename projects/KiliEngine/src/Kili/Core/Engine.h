#pragma once

#include "Kili/Core/TimeClock.h"
#include "Kili/Window.h"
#include "Kili/Logger/ConsoleLogger.h"
#include "Kili/Events/Event.h"
#include "Kili/Renderer/Shader.h"
#include "Kili/Renderer/VertexArray.h"

namespace Kili
{
    class Engine
    {
    private:
        ConsoleLogger* mConsoleLogger;
        Window* mWindow;
        TimeClock* mTimeClock;
        
        bool mIsRunning;
        bool mMinimized;
        
        bool mLoggingEvents;
        int mEventLogFilter;
        
        unsigned int mVertexArray; // Temp
        Shader* mShaderProgram;
        VertexBuffer* mVertexBuffer;
        IndexBuffer* mIndexBuffer;
        
        /**
         * Init all the engine components and set them up. \n
         * Init order :
         *  - Init log and console logger. So we can see errors.
         *  - Load Engine Config from "KiliEngine.ini".
         *  - Config log and console with their parameters.
         *  - Config event logging.
         *  - Init SDL3 components (only VIDEO and GAMEPAD for now).
         *  - Init and config window.
         *  - Init and config TimeClock.
         */
        void init();
        
        /**
         * Do an engine tick called while the engine is running. \n
         * Loop order :
         *  - Compute Time.
         *  - Poll sdl events in EventDispatcher.
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