#pragma once

#include "KeyBindings.hpp"

class IControl {
	public:
		IControl() {}
		virtual ~IControl() {}

		virtual void HandleKeyboardInput(Action action, float deltaTime) = 0;
		virtual void HandleMouseInput(double& x, double& y) = 0;
};