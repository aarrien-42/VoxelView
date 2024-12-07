#include "Window.hpp"

Window::Window(int width, int height, std::string title)
	: m_width(width), m_height(height)
{
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Set OpenGL version to 3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	// Check if the window was created successfully
	if (!m_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Make the window the current context
	glfwMakeContextCurrent(m_window);

	// Set the callback functions
	SetCallBacks();
}

Window::~Window()
{
	glfwTerminate();
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
	glfwPollEvents();
}

static void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
}

void Window::SetCallBacks()
{
	// Set the framebuffer size callback
	glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

	// Set the key callback
	glfwSetKeyCallback(m_window, KeyCallback);
}
