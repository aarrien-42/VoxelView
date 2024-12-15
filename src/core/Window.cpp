#include "Window.hpp"

Window::Window(int width, int height, std::string title)
	: m_window(nullptr), m_width(width), m_height(height), m_title(title)
{
	m_lastFrame = 0.0f;
	m_deltaTime = 0.0f;
}

Window::~Window()
{
	glfwTerminate();
}

int Window::GetWidth() const
{
	return m_width;
}

int Window::GetHeight() const
{
	return m_height;
}

float Window::GetDeltaTime() const
{
	return m_deltaTime;
}

GLFWwindow* Window::GetWindow() const
{
	return m_window;
}

int Window::GetKeyState(int key) const {
	return glfwGetKey(m_window, key);
}

bool Window::Init() {
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	// Set OpenGL version to 4.1 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	// Check if the window was created successfully
	if (!m_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Set the user pointer to the current instance
	glfwSetWindowUserPointer(m_window, this);

	// Make the window the current context
	glfwMakeContextCurrent(m_window);

	// Set the callback functions
	SetCallBacks();

	// Cursor mode
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::PollEvents()
{
	UpdateDeltaTime();
	glfwPollEvents();
}

void Window::UpdateDeltaTime()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	// Retrieve the Window instance from the GLFW window user pointer
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (win)
	{
		win->m_width = newWidth;
		win->m_height = newHeight;
		glViewport(0, 0, newWidth, newHeight);
	}
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
#ifdef _DEBUG
	std::cout << "Key: " << key << std::endl;
	std::cout << "Scancode: " << scancode << std::endl;
	std::cout << "Action: " << action << std::endl;
	std::cout << "Mods: " << mods << std::endl;
#endif
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	// Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	// win->GetCamera()->ProcessKeyboard(key, action, win->GetDeltaTime());
}

void Window::CursorPositionCallback(GLFWwindow* window, double currentX, double currentY)
{
	// Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	// win->GetCamera()->ProcessMouseMove(currentX, currentY);
}

void Window::SetCallBacks()
{
	// Set the framebuffer size callback
	glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

	// Set the key callback
	glfwSetKeyCallback(m_window, KeyCallback);

	// Set the cursor position callback
	glfwSetCursorPosCallback(m_window, CursorPositionCallback);
}
