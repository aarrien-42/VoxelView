#pragma once

#include "Renderer.hpp"
#include "Window.hpp"

#include "../graphics/Buffer.hpp"
#include "../graphics/VertexBufferLayout.hpp"
#include "../graphics/VertexArray.hpp"
#include "../graphics/Shader.hpp"
#include "../graphics/Texture.hpp"

class Application {
	public:
		Application(int width, int height, std::string title);
		~Application();

		bool Init();
		void Run();
	private:
		Window* m_window;
		Renderer* m_renderer;
};