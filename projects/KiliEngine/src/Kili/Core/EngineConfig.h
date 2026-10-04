#pragma once

#include "Kili/FileReadWrite/ConfigINI.h"

namespace Kili
{
    class EngineConfig
    {
    private:
        ConfigINI mConfig;
        
    public:
        explicit EngineConfig(const std::string& path) : mConfig(ConfigINI::readFile(path)) {}
        ~EngineConfig() = default;
        
        // Rule of zero
        EngineConfig(const EngineConfig&) = delete;
        EngineConfig(EngineConfig&& pOther) noexcept = delete;
        EngineConfig& operator=(const EngineConfig&) = delete;
        EngineConfig& operator=(EngineConfig&& pOther) noexcept = delete;
        
        [[nodiscard]] std::string getWindowName() const { return mConfig.getString("Window", "name", "DefaultName"); }
        [[nodiscard]] char getWindowFlags() const;
        [[nodiscard]] char getMsaa() const { return static_cast<char>(mConfig.getInt("Window", "msaa", 0)); }
        [[nodiscard]] unsigned int getWindowWidth() const { return mConfig.getInt("Window", "width", 400); }
        [[nodiscard]] unsigned int getWindowHeight() const { return mConfig.getInt("Window", "height", 600); }
        [[nodiscard]] bool isVsync() const { return mConfig.getBool("Window", "vsync"); }
        
        [[nodiscard]] bool isEventLogging() const { return mConfig.getBool("EventSystem", "logging", false); }
        [[nodiscard]] int getEventLogFilter() const;
        
        [[nodiscard]] int getConsoleLevelMask() const;
        
        [[nodiscard]] unsigned int getMaxFps() const { return mConfig.getInt("Time", "fps_max", 60); }
        [[nodiscard]] float getMaxDeltaTime() const { return mConfig.getFloat("Time", "max_delta_time", 1.0f); }
        [[nodiscard]] bool isFpsLogging() const { return mConfig.getBool("Time", "logging", false); }
        [[nodiscard]] float getFpsLogInterval() const { return mConfig.getFloat("Time", "log_interval", 1.0f); }
    };
}
