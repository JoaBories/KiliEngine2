#include "Engine.h"

namespace Kili
{
    Engine::Engine()
    {
        mConsoleLogger = new ConsoleLogger();
    }

    Engine::~Engine()
    {
        delete mConsoleLogger;
    }

    void Engine::run()
    {
        LOG_DEBUG("test debug");
        LOG_INFO("test info");
        LOG_LOADING("test loading");
        LOG_WARNING("test warning");
        LOG_ERROR("test error");
        
        while (true)
        {
        }
    }
}
