#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Window {
	public:
		Window(int width, int height, std::string title);
		~Window();

		bool Init();
		bool ShouldClose();
		void SwapBuffers();
		void PollEvents();
	private:
		void SetCallBacks();
		static void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	private:
		GLFWwindow* m_window;
		std::string m_title;
		int m_width, m_height;
};