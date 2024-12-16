#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Camera;

class Window {
	public:
		Window(int width, int height, std::string title);
		~Window();

		int GetWidth() const;
		int GetHeight() const;
		float GetDeltaTime() const;
		float GetFPS() const;
		void GetCursorPos(double &x, double& y);
		int GetKeyState(int key) const;

		bool Init();
		bool ShouldClose();
		void SwapBuffers();
		void PollEvents();
		void UpdateDeltaTime();
	private:
		void SetCallBacks();
		static void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double currentX, double currentY);
	private:
		GLFWwindow* m_window;

		std::string m_title;
		int m_width, m_height;
		float m_lastFrame;
		float m_deltaTime;
};