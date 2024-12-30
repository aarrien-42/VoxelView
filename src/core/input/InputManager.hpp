#pragma once

#include <GLFW/glfw3.h>

#include <vector>

#include "core/window/Window.hpp"
#include "KeyBindings.hpp"
#include "IControl.hpp"

class InputManager {
	public:
		InputManager (Window* window);
		~InputManager () = default;

		void Update ();
		void RegisterAgent (IControl* agent);
		void UnregisterAgent (IControl* agent);
	private:
		KeyBindings m_keyBindings;
		Window* m_window;
		std::vector<IControl*> m_agents;
};