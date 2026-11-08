#pragma once

#include "SDL3/SDL_scancode.h"
#include <array>
#include <glm/vec2.hpp>
#include "Kili/Core/Events/Event.h"

#define MAX_MOUSE_BUTTON 5

namespace Kili
{
	struct MouseInfos
	{
		glm::vec2 position;
		glm::vec2 delta;
	};
	
	class InputManager
	{
		static std::array<bool, SDL_SCANCODE_COUNT> mKeyDown;
		static std::array<bool, SDL_SCANCODE_COUNT> mKeyPressed;
		static std::array<bool, MAX_MOUSE_BUTTON> mMouseDown;
		static std::array<bool, MAX_MOUSE_BUTTON> mMousePressed;
	
		static MouseInfos mMouseInfo;
		static glm::vec2 mMouseScroll;

	public:
		static bool capturingMouse;

		static void init(const bool mouseTracking)
		{
			setMouseTracking(mouseTracking);
			capturingMouse = mouseTracking;
		}
	
		static void onEvent(const IEvent &e);
		static void beginFrame();

		/* Not implemented for the moment */
		static void setMouseTracking(bool pIsTracking) {} //todo
	
		constexpr static bool isKeyDown(const SDL_Scancode pKey) { return mKeyDown[pKey]; }
		constexpr static bool isKeyPressed(const SDL_Scancode pKey) { return mKeyPressed[pKey]; }
		
		static bool isMouseDown(const uint8_t pButton) { if (pButton <= MAX_MOUSE_BUTTON) return mMouseDown[pButton]; return false; }
		static bool isMousePressed(const uint8_t pButton) { if (pButton <= MAX_MOUSE_BUTTON) return mMousePressed[pButton]; return false; }
		
		static glm::vec2 getMouseDelta() { return mMouseInfo.delta; }
		static glm::vec2 getMousePos() { return mMouseInfo.position; }
		
		static glm::vec2 getMouseScroll() { return mMouseScroll; }
		static float getScrollY() { return mMouseScroll.y; }
	};
}