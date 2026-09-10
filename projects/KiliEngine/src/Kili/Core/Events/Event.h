#pragma once

#include "klpch.h"

namespace Kili
{
    enum class EventType : char
    {
        WindowClose, WindowResize, WindowFocus,
        
        InputKeyboard,
        InputMouseButton, InputMouseMove, InputMouseWheel,
        InputGamepadButton, InputGamepadAxis,
    };
    
    enum EventCategory : char
    {
        EventWindow     = BIT(0),
        EventInput      = BIT(1),
        EventKeyboard   = BIT(2),
        EventMouse      = BIT(3),
        EventGamepad    = BIT(4),
    };
    
    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        
        [[nodiscard]] virtual EventType getType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual int getCategoryFlags() const = 0;
        
        /** Used for Debug and logging **/
        [[nodiscard]] virtual std::string toString() const { return getName(); }
        
        /** Return true if the category is present. **/
        [[nodiscard]] bool hasCategory(const EventCategory category) const { return getCategoryFlags() & category; }
        /** Return true if at least one category is present. **/
        [[nodiscard]] bool hasCategories(const int categories) const { return (getCategoryFlags() & categories) != 0; }
    };
    
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
                               virtual EventType getType() const override { return getStaticType(); }\
                               virtual const char* getName() const override { return #type; }
    
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }
    
    template<typename T, typename F>
    bool DispatchEvent(const IEvent& event, const F& func)
    {
        if (event.getType() == T::getStaticType())
        {
            func(static_cast<const T&>(event));
            return true;
        }
        return false;
    }
}
