#include "ConsoleLogger.h"

#include <iomanip>
#include <iostream>
#include <sstream>


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
        
        std::string log;
        
        log.append("[");
        log.append(toString(message.level));
        log.append("] ");

        const time_t time = std::chrono::system_clock::to_time_t(message.timestamp);
        std::tm tm{};
        if (const errno_t err = localtime_s(&tm, &time); err) log.append("[timer error]");
        std::ostringstream oss;
        oss << std::put_time(&tm, "[%H:%M:%S] ");
        log.append(oss.str());
        
        log.append("[");
        log.append(message.file.substr(message.file.find_last_of("/\\") + 1)); // Keep only the filename and not the path
        log.append(" at line ");
        log.append(std::to_string(message.line));
        log.append("] ");
        
        log.append(message.message);

        std::cout << log << "\n";
    }
}