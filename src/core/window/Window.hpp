#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;


/**
* @brief Represents a window for the application
*/
class Window {
	public:
		Window (int width, int height, std::string title);
		~Window ();

		float GetDeltaTime () const;
		float GetFPS () const;
		void GetCursorPos (double& x, double& y);
		int GetKeyState (int key) const;

		bool Init ();
		bool ShouldClose ();
		void SwapBuffers ();
		void PollEvents ();
		void UpdateDeltaTime ();
	private:
		void SetCallBacks ();
		static void FramebufferSizeCallback (GLFWwindow* window, int newWidth, int newHeight);
		static void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPositionCallback (GLFWwindow* window, double currentX, double currentY);
		private:
		GLFWwindow* m_window;

		std::string m_title;
		float m_lastFrame;
		float m_deltaTime;
};