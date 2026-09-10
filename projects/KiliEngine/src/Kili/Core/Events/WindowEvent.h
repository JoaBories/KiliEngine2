#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    class WindowCloseEvent : public IEvent
    {
    public:
        WindowCloseEvent() = default;
        
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::EventWindow)
    };
    
    class WindowResizeEvent : public IEvent
    {
    protected:
        unsigned int mWidth, mHeight;
        
    public:
        WindowResizeEvent(const unsigned int width, const unsigned int height) : 
            mWidth(width), mHeight(height) {}
        
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::EventWindow)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window resize event : x : " + std::to_string(mWidth) + " y : " + std::to_string(mHeight);
        }
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
        
        // Todo implement proper window resize
    };
    
    class WindowFocusEvent : public IEvent
    {
    protected:
        bool mGained;
        
    public:
        explicit WindowFocusEvent(const bool gained) :
            mGained(gained) {}
        
        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategory::EventWindow)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window focus event : " + std::string(mGained ? "Gained" : "Lost");
        }
        
        [[nodiscard]] bool isGained() const { return mGained; }
    };
}