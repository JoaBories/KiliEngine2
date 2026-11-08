#pragma once
#include "Event.h"

namespace Kili
{
    class KeyboardEvent : public IEvent
    {
    protected:
        SDL_Scancode mKey;
        bool mIsDown;
        bool mIsRepeat;
        
    public:
        KeyboardEvent(const SDL_Scancode keycode, const bool down, const bool repeat) : 
            mKey(keycode), mIsDown(down), mIsRepeat(repeat) {}

        EVENT_CLASS_TYPE(InputKeyboard)
        EVENT_CLASS_CATEGORY(EventInput | EventKeyboard)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Key input event : " + std::to_string(mKey) + (mIsDown ? " Down" : " Up") + (mIsRepeat ? " Repeat" : "");
        }
        
        [[nodiscard]] SDL_Scancode getScancode() const { return mKey; }
        [[nodiscard]] bool isDown() const { return mIsDown; }
    };
    
    class MouseButtonEvent : public IEvent
    {
    protected:
        uint8_t mButton;
        bool mDown;
        glm::vec2 mMousePos;
        uint8_t mClicks;

    public:
        MouseButtonEvent(const uint8_t button, const bool down, const glm::vec2 mousePos, const uint8_t clicks) :
            mButton(button), mDown(down), mMousePos(mousePos), mClicks(clicks) {}
        
        EVENT_CLASS_TYPE(InputMouseButton)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse button input event : " + std::to_string(mButton) + (mDown ? " Down" : " Up") + " at " + std::format("({}, {})", mMousePos.x, mMousePos.y) + " / " + std::to_string(mClicks);
        }
        
        /** Return an unsigned int with the index of the button.\n 1 is left, 2 is middle and 3 is right */
        [[nodiscard]] uint8_t getButton() const { return mButton; }
        [[nodiscard]] bool isDown() const { return mDown; }
        [[nodiscard]] glm::vec2 getMousePos() const { return mMousePos; }
        [[nodiscard]] uint8_t getClicks() const { return mClicks; }
    };
    
    class MouseMoveEvent : public IEvent
    {
    protected:
        glm::vec2 mMousePos;
        glm::vec2 mMouseMove;
        
    public:
        MouseMoveEvent(const glm::vec2 mousePos, const glm::vec2 mouseMove) : 
            mMousePos(mousePos), mMouseMove(mouseMove) {}
        
        EVENT_CLASS_TYPE(InputMouseMove)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse move input event : " + std::format("({}, {})", mMousePos.x, mMousePos.y) + " / " + std::format("({}, {})", mMouseMove.x, mMouseMove.y);
        }
        
        [[nodiscard]] glm::vec2 getMousePos() const { return mMousePos; }
        [[nodiscard]] glm::vec2 getMouseMove() const { return mMouseMove; }
    };
    
    class MouseWheelEvent : public IEvent
    {
    protected:
        float mMouseScrollX, mMouseScrollY;
        glm::vec2 mMousePos;
        bool mFlipped;
        
    public:
        MouseWheelEvent(const float mouseScrollX, const float mouseScrollY, const glm::vec2 mousePos, const bool flipped) : 
            mMouseScrollX(mouseScrollX), mMouseScrollY(mouseScrollY), mMousePos(mousePos), mFlipped(flipped) {}
        
        EVENT_CLASS_TYPE(InputMouseWheel)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse wheel input event : x : " + std::to_string(mMouseScrollX) + " y : " + std::to_string(mMouseScrollY) + " / " + std::format("({}, {})", mMousePos.x, mMousePos.y);
        }
        
        [[nodiscard]] float getMouseScrollX() const { return mMouseScrollX; } /* right positive, left negative. */
        [[nodiscard]] float getMouseScrollY() const { return mMouseScrollY; } /* Away from the user positive, toward the user negative. */
        [[nodiscard]] glm::vec2 getMousePos() const { return mMousePos; }
        [[nodiscard]] bool isFlipped() const { return mFlipped; }
    };
    
    class GamepadButtonEvent : public IEvent
    {
    protected:
        SDL_GamepadButton mGamepadButton;
        bool mDown;
        
    public:
        GamepadButtonEvent(const uint8_t button, const bool down) : 
            mGamepadButton(static_cast<SDL_GamepadButton>(button)), mDown(down) {}
        
        EVENT_CLASS_TYPE(InputGamepadButton)
        EVENT_CLASS_CATEGORY(EventInput | EventGamepad)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Gamepad button input event : " + std::to_string(mGamepadButton) + " / " + (mDown ? " Down" : " Up");
        }
        
        [[nodiscard]] SDL_GamepadButton getGamepadButton() const { return mGamepadButton; }
        [[nodiscard]] bool isDown() const { return mDown; }
    };
    
    class GamepadAxisEvent : public IEvent
    {
    protected:
        SDL_GamepadAxis mGamepadAxis;
        short mGamepadAxisValue;
        
    public:
        GamepadAxisEvent(const uint8_t axis, const short axisValue) : 
            mGamepadAxis(static_cast<SDL_GamepadAxis>(axis)), mGamepadAxisValue(axisValue) {}
        
        EVENT_CLASS_TYPE(InputGamepadAxis)
        EVENT_CLASS_CATEGORY(EventInput | EventGamepad)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Gamepad axis input event : " + std::to_string(mGamepadAxis) + " / " + std::to_string(getGamepadAxisValueNormalized());
        }
        
        [[nodiscard]] SDL_GamepadAxis getGamepadAxis() const { return mGamepadAxis; }
        /** Scaling from -32768 to 32768. (IDK, this is a SDL3 thing)*/
        [[nodiscard]] short getGamepadAxisValue() const { return mGamepadAxisValue; }
        [[nodiscard]] float getGamepadAxisValueNormalized() const { return static_cast<float>(mGamepadAxisValue) / 32768.0f; }
    };
}