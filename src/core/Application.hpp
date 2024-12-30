#pragma once

#include "graphics/Renderer.hpp"
#include "scene/Camera.hpp"
#include "core/window/Window.hpp"
#include "core/input/InputManager.hpp"

#include "graphics/OpenGL/Buffer.hpp"
#include "graphics/OpenGL/VertexBufferLayout.hpp"
#include "graphics/OpenGL/VertexArray.hpp"
#include "graphics/OpenGL/Shader.hpp"
#include "graphics/OpenGL/Texture.hpp"

/**
* @brief Main application class
*/
class Application {
	public:
		Application (int width, int height, std::string title);
		~Application ();

		bool Init ();
		void Run ();
	private:
		Window* m_window;
		Renderer* m_renderer;
};