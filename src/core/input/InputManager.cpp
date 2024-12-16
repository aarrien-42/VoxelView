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
	// Poll window events and handle input for all registered agents
	m_window->PollEvents();

	// Handle mouse input
	double x = 0.0, y = 0.0;
	m_window->GetCursorPos(x, y);
	for (IControl* agent : m_agents) {
		agent->HandleMouseInput(x, y);
	}

	// Handle keyboard input
	float deltaTime = m_window->GetDeltaTime();
	std::vector<int>keys = m_keyBindings.GetBindKeys();
	for (int key : keys) {
		if (m_window->GetKeyState(key) == GLFW_PRESS) {
			for (IControl* agent : m_agents) {
				Action action = m_keyBindings.GetKeyAction(key);
				agent->HandleKeyboardInput(action, deltaTime);
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