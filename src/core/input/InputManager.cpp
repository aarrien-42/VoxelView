#include "InputManager.hpp"

#include <algorithm>

InputManager::InputManager(Window* window) : m_window(window)
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	m_window->PollEvents();

	double x = 0.0, y = 0.0;
	m_window->GetCursorPos(x, y);
	for (size_t j = 0; j < m_agents.size(); j++) {
		m_agents[j]->HandleMouseInput(x, y);
	}

	float deltaTime = m_window->GetDeltaTime();
	std::vector<int>keys = m_keyBindings.GetBindKeys();
	for (size_t i = 0; i < keys.size(); i++) {
		if (m_window->GetKeyState(keys[i]) == GLFW_PRESS) {
			for (size_t j = 0; j < m_agents.size(); j++) {
				m_agents[j]->HandleKeyboardInput(m_keyBindings.GetKeyAction(keys.at(i)), deltaTime);
			}
		}
	}
}
void InputManager::RegisterAgent(IControl* agent)
{
	m_agents.push_back(agent);
}

void InputManager::UnregisterAgent(IControl* agent)
{
	// TODO: Implement
}