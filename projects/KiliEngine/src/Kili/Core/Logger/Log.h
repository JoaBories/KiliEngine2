#pragma once
#include "klpch.h"

/*
*   Simple class for logging in the engine and other applications :
*       -Use macros for logging at different levels.
*       -You can create a logger inheriting from ILogger and subscribing with addLogger().
*       -Logs are getting the file and the line where it was called and the timestamp.
*/

namespace Kili
{
    enum LogLevel : char
    {
        Debug   = BIT(0),
        Info    = BIT(1),
        Loading = BIT(2),
        Warning = BIT(3),
        Error   = BIT(4),
    };

    inline std::string toString(const LogLevel e)
    {
        switch (e)
        {
            case LogLevel::Debug: return "Debug";
            case LogLevel::Info: return "Info";
            case LogLevel::Loading: return "Loading";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Error: return "Error";
            default: return "unknown";
        }
    }

    struct LogMessage
    {
        std::string message;
        std::string file;
        std::chrono::system_clock::time_point timestamp;
        int line;
        LogLevel level;
    };
    
    class ILogger
    {
    public:
        virtual void receiveLog(const LogMessage& message) = 0;
        virtual ~ILogger() = default;
    };
    
    class Log
    {
    private:
        std::vector<ILogger*> mLoggers;
        
        Log() = default;
        ~Log() { mLoggers.clear(); }
        
    public:
        static Log* instance()
        {
            static Log instance;
            return &instance;
        }
        
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;
        
        void addLogger(ILogger* logger);
        void removeLogger(const ILogger* logger);
        
        void log(LogLevel level, const std::string& message, const std::string& file, int line) const;
    };

#define LOG_DEBUG(msg) Log::instance()->log(LogLevel::Debug, msg, __FILE__, __LINE__)
#define LOG_INFO(msg) Log::instance()->log(LogLevel::Info, msg, __FILE__, __LINE__)
#define LOG_LOADING(msg) Log::instance()->log(LogLevel::Loading, msg, __FILE__, __LINE__)
#define LOG_WARNING(msg) Log::instance()->log(LogLevel::Warning, msg, __FILE__, __LINE__)
#define LOG_ERROR(msg) Log::instance()->log(LogLevel::Error, msg, __FILE__, __LINE__)
    
#define TEST_ALL_LOG LOG_DEBUG("Test Debug"); LOG_INFO("Test Info"); LOG_LOADING("Test Loading"); LOG_WARNING("Test Warning"); LOG_ERROR("Test Error");
}
