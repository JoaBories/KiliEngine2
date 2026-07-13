#pragma once

namespace Kili
{
    class Engine
    {
    public:
        Engine();
        virtual ~Engine();
        
        void run();
    };
    
    // To be defined in runtime app
    Engine* createEngine();
}