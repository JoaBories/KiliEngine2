#include "klpch.h"
#include "InputManager.h"

#include "Events/InputEvent.h"

namespace Kili
{
	std::array<bool, SDL_SCANCODE_COUNT> InputManager::mKeyDown{false};
	std::array<bool, SDL_SCANCODE_COUNT> InputManager::mKeyPressed{false};
	std::array<bool, MAX_MOUSE_BUTTON> InputManager::mMouseDown{false};
	std::array<bool, MAX_MOUSE_BUTTON> InputManager::mMousePressed{false};
	
	MouseInfos InputManager::mMouseInfo{};
	glm::vec2 InputManager::mMouseScroll{};
	
	bool InputManager::capturingMouse = false;
	
	void InputManager::onEvent(const IEvent& e)
	{
		DispatchEvent<KeyboardEvent>(e, [&](const KeyboardEvent& event)
		{
			if (event.getScancode() < SDL_SCANCODE_COUNT)
			{
				mKeyDown[event.getScancode()] = event.isDown();
				mKeyPressed[event.getScancode()] = event.isDown();
			}
		});
		
		DispatchEvent<MouseButtonEvent>(e, [&](const MouseButtonEvent& event)
		{
			if (event.getButton() <= MAX_MOUSE_BUTTON)
			{
				mMouseDown[event.getButton()] = event.isDown();
				mMousePressed[event.getButton()] = event.isDown();
			}
		});
		
		DispatchEvent<MouseMoveEvent>(e, [&](const MouseMoveEvent& event)
		{
			mMouseInfo = { event.getMousePos(), event.getMouseMove() };
		});
		
		DispatchEvent<MouseWheelEvent>(e, [&](const MouseWheelEvent& event)
		{
			mMouseScroll = { event.getMouseScrollX(), event.getMouseScrollY() };
		});
	}
	
	void InputManager::beginFrame()
	{
		mMouseInfo = {};
		mMouseScroll = {};
		
		mKeyDown = {false};
		mMouseDown = {false};
	}
}