#pragma once

#include <GLFW/glfw3.h>

#include <vector>

enum Action {
	UNKNOWN,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class KeyBindings {
	public:
		KeyBindings() {}
		~KeyBindings() {}

		bool BindKey(int key, Action action);
		std::vector<int> GetBindKeys () const;
		Action GetKeyAction (int key) const;
	private:
		int m_forward = GLFW_KEY_W;
		int m_backward = GLFW_KEY_S;
		int m_left = GLFW_KEY_A;
		int m_right = GLFW_KEY_D;
		int m_up = GLFW_KEY_SPACE;
		int m_down = GLFW_KEY_LEFT_SHIFT;
};