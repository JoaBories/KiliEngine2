#include "klpch.h"
#include "Engine.h"

#include "Kili/Core/EngineConfig.h"

#include "Kili/Core/Events/InputEvent.h"
#include "Kili/Core/Events/WindowEvent.h"
#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlShader.h"
#include "Kili/Scene/DefaultScene.h"
#include "Kili/Scene/SceneManager.h"

namespace Kili
{
    void Engine::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_QUIT:
                onEvent(WindowCloseEvent());
                break;
                
            case SDL_EVENT_KEY_DOWN:
                onEvent(KeyboardEvent(event.key.key, true, event.key.repeat));
                break;
                
            case SDL_EVENT_KEY_UP:
                onEvent(KeyboardEvent(event.key.key, false, event.key.repeat));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onEvent(MouseButtonEvent(
                    event.button.button, true, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onEvent(MouseButtonEvent(
                    event.button.button, false, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_MOTION:
                onEvent(MouseMoveEvent(
                    Vector2{event.motion.x, event.motion.y}, 
                    Vector2{event.motion.xrel, event.motion.yrel}));
                break;
                
            case SDL_EVENT_MOUSE_WHEEL:
                onEvent(MouseWheelEvent(
                    event.wheel.x, 
                    event.wheel.y, 
                    Vector2{event.wheel.mouse_x, event.wheel.mouse_y}, 
                    event.wheel.direction));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                onEvent(GamepadButtonEvent(event.gbutton.button, true));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                onEvent(GamepadButtonEvent(event.gbutton.button, false));
                break;
                
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                onEvent(GamepadAxisEvent(event.gaxis.axis, event.gaxis.value));
                break;
                
            case SDL_EVENT_WINDOW_RESIZED:
                onEvent(WindowResizeEvent(event.window.data1, event.window.data2));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                onEvent(WindowFocusEvent(true));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                onEvent(WindowFocusEvent(false));
                break;
                
            default:
                break;
            }
        }
    }
    
    void Engine::onEvent(const IEvent& event)
    {
        // Catch window close event
        DispatchEvent<WindowCloseEvent>(event, [this](const WindowCloseEvent& e) { mIsRunning = false; });
        DispatchEvent<WindowFocusEvent>(event, [this](const WindowFocusEvent& e) { mMinimized = !e.isGained(); });
        
        //Future possible usages of events :
        //mInputManager->onEvent(event);
        //mWindow->onEvent(event);
        
        if (mLoggingEvents)
        {
            if (event.hasCategories(mEventLogFilter)) return;
            LOG_DEBUG(event.toString());
        }
    }
    
    Engine::Engine() : 
        mConsoleLogger(nullptr),
        mWindow(nullptr),
        mTimeClock(nullptr),
        mIsRunning(false), mMinimized(false), 
        mLoggingEvents(false), mEventLogFilter(0)
    {
    }

    void Engine::run()
    {
        init();
        
        mIsRunning = true;
        
        while (mIsRunning)
        {
            loop();
        }
        
        close();
    }

    void Engine::init()
    {
        // Init log
        Log::instance(); // Ensure a first initialization of the log
        mConsoleLogger = new ConsoleLogger();
        
        LOG_LOADING("KiliEngine Initialization");
        
        // Load config
        const EngineConfig config("config/KiliEngine.ini", "KiliEngine");
        LOG_LOADING("Config loaded");
        
        // Config logs and events
        mConsoleLogger->setLogLevelMask(config.getConsoleLevelMask());
        
        mLoggingEvents = config.isEventLogging();
        mEventLogFilter = config.getEventLogFilter();
        
        // SDL init
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        if (!SDL_Init(SDL_INIT_GAMEPAD)) LOG_ERROR("SDL GAMEPAD could not initialize");     // TODO make gamepad working
        else LOG_LOADING("SDL GAMEPAD initialized");
        
        // Init and config window
        const WindowParameters winParams{ config.getWindowWidth(), config.getWindowHeight(), config.getWindowFlags(), config.getMsaa(), config.isVsync()};
        mWindow = new Window(config.getWindowName(), winParams);
        
        if (!mWindow->init())  LOG_ERROR("Window could not initialize");
        else LOG_LOADING("Window initialized");
        
        //Temp
        glGenVertexArrays(1, &mVertexArray);
        glBindVertexArray(mVertexArray);

        float vertices[3*3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };
        
        unsigned long indices[3] = {
            0, 1, 2
        };
        
        mVertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

        mIndexBuffer = IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned long));
        
        mShaderProgram = Shader::create("Test", {"resources/Test.vert", "resources/Test.frag"});
        mShaderProgram->load();
        
        // Init and config time clock
        mTimeClock = new TimeClock(config.getMaxFps(), config.getMaxDeltaTime());
        mTimeClock->setLogging(config.isFpsLogging());
        mTimeClock->setLoggingInterval(config.getFpsLogInterval());
        
        SceneManager::setScenes({new DefaultScene()});
        
        LOG_LOADING("KiliEngine Initialized");
    }

    void Engine::loop()
    {
        mTimeClock->computeTime();
        
        pollEvents();
        
        //update
        SceneManager::update();
        
        if (!mMinimized)
        {
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            mShaderProgram->setActive();
            
            //render
            glBindVertexArray(mVertexArray);
            glDrawElements(GL_TRIANGLES, mIndexBuffer->count(), GL_UNSIGNED_INT, nullptr);
        }
        
        SceneManager::loadReload();
        
        mWindow->update();
        
        mTimeClock->delayTime();
    }

    void Engine::close()
    {
        mShaderProgram->unload();
        
        SceneManager::close();
        
        delete mWindow;
        mWindow = nullptr;
        
        delete mTimeClock;
        mTimeClock = nullptr;
        
        SDL_Quit();
        
        LOG_LOADING("KiliEngine Ended");
        
        delete mConsoleLogger;
        mConsoleLogger = nullptr;
    }
}
