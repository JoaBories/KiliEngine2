#pragma once

#include "Log.h"

namespace Kili
{
    class ConsoleLogger : public ILogger
    {
    private:
        LogLevel mMinLevel;
        
    public:
        explicit ConsoleLogger(LogLevel minLevel = LogLevel::Debug);
        ~ConsoleLogger() override;
    
        void receiveLog(const LogMessage& message) override;
    
    };
}
