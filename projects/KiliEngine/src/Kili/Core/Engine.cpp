#include "klpch.h"
#include "Engine.h"

#include "Kili/Core/TimeClock.h"

#include "Kili/Core/EngineConfig.h"

#include "Kili/Core/Events/InputEvent.h"
#include "Kili/Core/Events/WindowEvent.h"

#include "Kili/Rendering/Renderer.h"

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
                    
                case SDL_EVENT_WINDOW_MINIMIZED:
                    onEvent(WindowMinimizedEvent());
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
        DispatchEvent<KeyboardEvent>(event, [this](const KeyboardEvent& e) { if (e.getKey() == SDLK_ESCAPE) mIsRunning = false; } );
        
        DispatchEvent<WindowFocusEvent>(event, [this](const WindowFocusEvent& e) { if (e.isGained()) mMinimized = false; } );
        DispatchEvent<WindowMinimizedEvent>(event, [this](const WindowMinimizedEvent& e) { mMinimized = true; });
        
        Renderer::onEvent(event);
        SceneManager::onEvent(event);
        
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
        mConsoleLogger.reset(new ConsoleLogger());
        
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
        mWindow.reset(new Window(config.getWindowName(), winParams));
        
        if (!mWindow->init())  LOG_ERROR("Window could not initialize");
        else LOG_LOADING("Window initialized");
        
        Renderer::onEvent(WindowResizeEvent(winParams.width, winParams.height)); // TODO clean that shit
        
        // Init and config time clock
        TimeClock::init(config.getMaxFps(), config.getMaxDeltaTime());
        TimeClock::setLogging(config.isFpsLogging());
        TimeClock::setLoggingInterval(config.getFpsLogInterval());
        
        LOG_LOADING("KiliEngine Initialized");
        
        SceneManager::setScenes({new DefaultScene()});
        SceneManager::loadScene(0);
    }

    void Engine::loop()
    {
        TimeClock::computeTime();
        
        pollEvents();
        
        //update
        SceneManager::update();
        
        if (!mMinimized)
        {
            Renderer::beginScene(CameraManager::getActiveCamera());
            
            SceneManager::render();
            
            Renderer::endScene();
        }
        
        SceneManager::loadReload();
        
        mWindow->update();
        
        TimeClock::delayTime();
    }

    void Engine::close()
    {
        SceneManager::close();
        
        mWindow.reset();
        
        SDL_Quit();
        
        LOG_LOADING("KiliEngine Ended");
        
        mConsoleLogger.reset();
    }
}
