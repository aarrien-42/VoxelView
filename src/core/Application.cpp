#include "Application.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Application::Application (int width, int height, std::string title)
{
	m_window = new Window (width, height, title);
	m_renderer = new Renderer ();
}

Application::~Application ()
{
	delete m_window;
	delete m_renderer;
}

bool Application::Init ()
{
	if (!m_window->Init ())
	{
		std::cerr << "Failed to initialize window" << std::endl;
		return false;
	}

	if (!m_renderer->Init ())
	{
		std::cerr << "Failed to initialize renderer" << std::endl;
		return false;
	}

	return true;
}

void Application::Run ()
{
	// Block
	Block block (BlockType::BEDROCK, glm::vec3 (0.0f, 0.0f, 0.0f));
	TextureArray textures (block.GetTexturePaths ());
	Shader shader ("../res/shaders/basic.vert", "../res/shaders/basic.frag");

	// Text
	Font font ("../res/fonts/arial.ttf", 48);
	Text text ("Hello world!", font);
	text.SetPosition (glm::vec2 (100.0f, 500.0f));
	text.SetColor (glm::vec3 (0.0f, 1.0f, 1.0f));
	Shader textShader ("../res/shaders/text.vert", "../res/shaders/text.frag");

	Camera camera;
	InputManager inputManager (m_window);
	inputManager.RegisterAgent (&camera);
	m_renderer->SetCamera (camera);

	while (!m_window->ShouldClose ())
	{
		// Clear the screen
		m_renderer->Clear ();

		// Draw
		textures.Bind ();
		block.SetPosition (glm::vec3 (0.0f, 0.0f, 0.0f));
		m_renderer->Draw (block, shader);
		block.SetPosition (glm::vec3 (2.0f, 0.0f, 0.0f));
		m_renderer->Draw (block, shader);

		// Draw text
		m_renderer->Draw (text, textShader);

		// Swap the buffers
		m_window->SwapBuffers ();

		// Update the input events
		inputManager.Update ();

		// Print the FPS
		double currentTime = glfwGetTime ();
		static float lastPrintTime = currentTime;
		if (currentTime - lastPrintTime >= 0.5)
		{
			std::cout << "\rFPS: " << (int)m_window->GetFPS () << "         " << std::flush;
			lastPrintTime = currentTime;
		}
	}
}
