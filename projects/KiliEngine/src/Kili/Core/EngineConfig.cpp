#include "klpch.h"
#include "EngineConfig.h"

#include "Kili/Window.h"
#include "Kili/Core/Logger/Log.h"
#include "Kili/Core/Events/Event.h"

char Kili::EngineConfig::getWindowFlags() const
{
    char windowFlags = 0;
    if (mConfig.getBool("Window", "fullscreen")) windowFlags |= EnumWindowFlags::WindowFullscreen;
    if (mConfig.getBool("Window", "borderless")) windowFlags |= EnumWindowFlags::WindowBorderless;
    if (mConfig.getBool("Window", "resizable")) windowFlags |= EnumWindowFlags::WindowResizable;
    if (mConfig.getBool("Window", "always_on_top")) windowFlags |= EnumWindowFlags::WindowAlwaysOnTop;
    return windowFlags;
}

int Kili::EngineConfig::getEventLogFilter() const
{
    int eventLogMask = 0;
    if (!mConfig.getBool("EventSystem", "logging_mouse_events")) eventLogMask |= EventCategory::EventMouse;
    if (!mConfig.getBool("EventSystem", "logging_keyboard_events")) eventLogMask |= EventCategory::EventKeyboard;
    return eventLogMask;
}

int Kili::EngineConfig::getConsoleLevelMask() const
{
    int consoleLevelMask = 0;
    if (!mConfig.getBool("Console", "logging_info", true)) consoleLevelMask |= LogLevel::Info;
    if (!mConfig.getBool("Console", "logging_debug", true)) consoleLevelMask |= LogLevel::Debug;
    if (!mConfig.getBool("Console", "logging_loading", true)) consoleLevelMask |= LogLevel::Loading;
    if (!mConfig.getBool("Console", "logging_warning", true)) consoleLevelMask |= LogLevel::Warning;
    if (!mConfig.getBool("Console", "logging_error", true)) consoleLevelMask |= LogLevel::Error;
    return consoleLevelMask;
}
