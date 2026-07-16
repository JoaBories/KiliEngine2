#include "klpch.h"
#include "ConsoleLogger.h"

namespace Kili
{
    ConsoleLogger::ConsoleLogger(const LogLevel minLevel) : mMinLevel(minLevel)
    {
        Log::instance().addLogger(this);
    }
    
    ConsoleLogger::~ConsoleLogger()
    {
        Log::instance().removeLogger(this);
    }

    void ConsoleLogger::receiveLog(const LogMessage& message)
    {
        if (message.level < mMinLevel) return;
        
        std::ostringstream log;
        
        log << "[" << toString(message.level) << "] ";

        const time_t time = std::chrono::system_clock::to_time_t(message.timestamp);
        std::tm tm{};
        if (const errno_t err = localtime_s(&tm, &time); err)
        {
            log << "[timer error] ";
        }
        else
        {
            log << std::put_time(&tm, "[%H:%M:%S] ");
        }

        const std::string filename = message.file.substr(message.file.find_last_of("/\\") + 1); // Keep only the filename and not the path
        log << "[" << filename << " at line " << message.line << "] ";
        
        log << message.message;

        if (message.level >= LogLevel::Warning) std::cerr << log.str() << "\n";
        else                                    std::cout << log.str() << "\n";
    }
}