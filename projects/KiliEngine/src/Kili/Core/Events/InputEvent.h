#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    class KeyboardEvent : public IEvent
    {
    protected:
        SDL_Keycode mKey;
        bool mIsDown;
        bool mIsRepeat;
        
    public:
        KeyboardEvent(const SDL_Keycode keycode, const bool down, const bool repeat) : 
            mKey(keycode), mIsDown(down), mIsRepeat(repeat) {}

        EVENT_CLASS_TYPE(InputKeyboard)
        EVENT_CLASS_CATEGORY(EventInput | EventKeyboard)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Key input event : " + std::to_string(mKey) + (mIsDown ? " Down" : " Up") + (mIsRepeat ? " Repeat" : "");
        }
        
        [[nodiscard]] SDL_Keycode getKey() const { return mKey; }
        [[nodiscard]] bool isDown() const { return mIsDown; }
    };
    
    class MouseButtonEvent : public IEvent
    {
    protected:
        Uint8 mButton;
        bool mDown;
        Vector2 mMousePos;
        Uint8 mClicks;

    public:
        MouseButtonEvent(const Uint8 button, const bool down, const Vector2 mousePos, const Uint8 clicks) :
            mButton(button), mDown(down), mMousePos(mousePos), mClicks(clicks) {}
        
        EVENT_CLASS_TYPE(InputMouseButton)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse button input event : " + std::to_string(mButton) + (mDown ? " Down" : " Up") + " at " + mMousePos.toString() + " / " + std::to_string(mClicks);
        }
        
        /** Return an unsigned int with the index of the button.\n 1 is left, 2 is middle and 3 is right */
        [[nodiscard]] Uint8 getButton() const { return mButton; }
        [[nodiscard]] bool isDown() const { return mDown; }
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] Uint8 getClicks() const { return mClicks; }
    };
    
    class MouseMoveEvent : public IEvent
    {
    protected:
        Vector2 mMousePos;
        Vector2 mMouseMove;
        
    public:
        MouseMoveEvent(const Vector2 mousePos, const Vector2 mouseMove) : 
            mMousePos(mousePos), mMouseMove(mouseMove) {}
        
        EVENT_CLASS_TYPE(InputMouseMove)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse move input event : " + mMousePos.toString() + " / " + mMouseMove.toString();
        }
        
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] Vector2 getMouseMove() const { return mMouseMove; }
    };
    
    class MouseWheelEvent : public IEvent
    {
    protected:
        float mMouseScrollX, mMouseScrollY;
        Vector2 mMousePos;
        bool mFlipped;
        
    public:
        MouseWheelEvent(const float mouseScrollX, const float mouseScrollY, const Vector2 mousePos, const bool flipped) : 
            mMouseScrollX(mouseScrollX), mMouseScrollY(mouseScrollY), mMousePos(mousePos), mFlipped(flipped) {}
        
        EVENT_CLASS_TYPE(InputMouseWheel)
        EVENT_CLASS_CATEGORY(EventInput | EventMouse)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse wheel input event : x : " + std::to_string(mMouseScrollX) + " y : " + std::to_string(mMouseScrollY) + " / " + mMousePos.toString();
        }
        
        [[nodiscard]] float getMouseScrollX() const { return mMouseScrollX; } /* Right positive, left negative. */
        [[nodiscard]] float getMouseScrollY() const { return mMouseScrollY; } /* Away from the user positive, toward the user negative. */
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] bool isFlipped() const { return mFlipped; }
    };
    
    class GamepadButtonEvent : public IEvent
    {
    protected:
        SDL_GamepadButton mGamepadButton;
        bool mDown;
        
    public:
        GamepadButtonEvent(const Uint8 button, const bool down) : 
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
        Sint16 mGamepadAxisValue;
        
    public:
        GamepadAxisEvent(const Uint8 axis, const Sint16 axisValue) : 
            mGamepadAxis(static_cast<SDL_GamepadAxis>(axis)), mGamepadAxisValue(axisValue) {}
        
        EVENT_CLASS_TYPE(InputGamepadAxis)
        EVENT_CLASS_CATEGORY(EventInput | EventGamepad)
        
        [[nodiscard]] std::string toString() const override
        {
            return "Gamepad axis input event : " + std::to_string(mGamepadAxis) + " / " + std::to_string(getGamepadAxisValueNormalized());
        }
        
        [[nodiscard]] SDL_GamepadAxis getGamepadAxis() const { return mGamepadAxis; }
        /** Scaling from -32768 to 32768. (IDK this is a SDL3 thing)*/
        [[nodiscard]] Sint16 getGamepadAxisValue() const { return mGamepadAxisValue; }
        [[nodiscard]] float getGamepadAxisValueNormalized() const { return static_cast<float>(mGamepadAxisValue) / 32768.0f; }
    };
}