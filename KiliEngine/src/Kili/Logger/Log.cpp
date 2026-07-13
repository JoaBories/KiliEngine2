#include "Log.h"

namespace Kili
{
    void Log::addLogger(ILogger* logger)
    {
        if (const auto iter = std::find(mLoggers.begin(), mLoggers.end(), logger); iter == mLoggers.end()) 
            mLoggers.push_back(logger);
    }
    
    void Log::removeLogger(const ILogger* logger)
    {
        if (const auto iter = std::find(mLoggers.begin(), mLoggers.end(), logger); iter != mLoggers.end()) 
            mLoggers.erase(iter);
    }
    
    void Log::log(const LogLevel level, const std::string& message, const std::string& file, const int line) const
    {
        const LogMessage logMessage{message, file, std::chrono::system_clock::now(), line, level};

        for (ILogger* logger : mLoggers)
        {
            logger->receiveLog(logMessage);
        }
    }
}
