#include "KeyBindings.hpp"

KeyBindings::KeyBindings(BindingPreset preset) : m_preset(preset) {
	InitBindings();
	UpdateBindings();
}

void KeyBindings::SetPreset(BindingPreset preset) {
	m_preset = preset;
	UpdateBindings();
}

void KeyBindings::SetDefaultBindings() {
	m_forward = GLFW_KEY_W;
	m_backward = GLFW_KEY_S;
	m_left = GLFW_KEY_A;
	m_right = GLFW_KEY_D;
	m_up = GLFW_KEY_SPACE;
	m_down = GLFW_KEY_LEFT_SHIFT;
}

void KeyBindings::InitBindings() {
	m_forward = GLFW_KEY_UNKNOWN;
	m_backward = GLFW_KEY_UNKNOWN;
	m_left = GLFW_KEY_UNKNOWN;
	m_right = GLFW_KEY_UNKNOWN;
	m_up = GLFW_KEY_UNKNOWN;
	m_down = GLFW_KEY_UNKNOWN;
}

void KeyBindings::UpdateBindings() {
	switch (m_preset) {
	case BindingPreset::DEFAULT:
		SetDefaultBindings();
		break;
	}
}

bool KeyBindings::BindKey(int key, Action action) {
	switch (action) {
		case Action::FORWARD: {
			m_forward = key;
			return true;
		}
		case Action::BACKWARD: {
			m_backward = key;
			return true;
		}
		case Action::LEFT: {
			m_left = key;
			return true;
		}
		case Action::RIGHT: {
			m_right = key;
			return true;
		}
		case Action::UP: {
			m_up = key;
			return true;
		}
		case Action::DOWN: {
			m_down = key;
			return true;
		}
		default:
			return false;
	}
}

std::vector<int> KeyBindings::GetBindKeys() const {
	std::vector<int> keys;
	keys.push_back(m_forward);
	keys.push_back(m_backward);
	keys.push_back(m_left);
	keys.push_back(m_right);
	keys.push_back(m_up);
	keys.push_back(m_down);
	return keys;
}

Action KeyBindings::GetKeyAction(int key) const {
	if (key == m_forward) {
		return Action::FORWARD;
	}
	else if (key == m_backward) {
		return Action::BACKWARD;
	}
	else if (key == m_left) {
		return Action::LEFT;
	}
	else if (key == m_right) {
		return Action::RIGHT;
	}
	else if (key == m_up) {
		return Action::UP;
	}
	else if (key == m_down) {
		return Action::DOWN;
	}
	else {
		return Action::UNKNOWN;
	}
}