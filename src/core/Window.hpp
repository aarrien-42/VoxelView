#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Window {
	public:
		Window(int width, int height, std::string title);
		~Window();

		bool ShouldClose();
		void SwapBuffers();
		void PollEvents();
	private:
		void SetCallBacks();
	private:
		GLFWwindow* m_window;
		int m_width, m_height;
};