#pragma once

#include "KeyBindings.hpp"

/**
* @brief Interface for input control
*/
class IControl {
	public:
		IControl () = default;
		virtual ~IControl () = default;

		virtual void HandleKeyboardInput (Action action, float deltaTime) = 0;
		virtual void HandleMouseInput (double& x, double& y) = 0;
};