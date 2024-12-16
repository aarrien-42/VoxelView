#pragma once

#include <GLFW/glfw3.h>

#include <vector>

enum BindingPreset {
	DEFAULT
};

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
		KeyBindings(BindingPreset preset = BindingPreset::DEFAULT);
		~KeyBindings() = default;

		void SetPreset(BindingPreset preset);
		void SetDefaultBindings();

		void InitBindings();
		void UpdateBindings();
		bool BindKey(int key, Action action);
		std::vector<int> GetBindKeys () const;
		Action GetKeyAction (int key) const;
	private:
		BindingPreset m_preset;

		int m_forward;
		int m_backward;
		int m_left;
		int m_right;
		int m_up;
		int m_down;
};