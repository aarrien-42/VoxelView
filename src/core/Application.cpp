#include "Application.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Application::Application(int width, int height, std::string title)
{
	m_window = new Window(width, height, title);
	m_renderer = new Renderer();
}

Application::~Application()
{
	delete m_window;
	delete m_renderer;
}

bool Application::Init()
{
	if (!m_window->Init()) {
		std::cerr << "Failed to initialize window" << std::endl;
		return false;
	}

	if (!m_renderer->Init()) {
		std::cerr << "Failed to initialize renderer" << std::endl;
		return false;
	}

	return true;
}

void Application::Run()
{
	float vertices[] = {
	 // position         // color           // texture

	// FRONT
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 0
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 1
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 3

	// BACK
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 4
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 5
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 6
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 7

	// LEFT
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 8
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 9
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // 10
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 11

	// RIGTH
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 12
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 13
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // 14
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 15

	// TOP
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 16
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 17
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 18
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 19

	// BOTTOM
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 20
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 21
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 22
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 23
	 
	};

	unsigned int indices[] = {
		// FRONT
		0, 2, 1,
		0, 2, 3,
		// BACK
		4, 6, 5,
		4, 6, 7,
		// LEFT
		8, 10, 9,
		8, 10, 11,
		// RIGHT
		12, 14, 13,
		12, 14, 15,
		// TOP
		16, 18, 17,
		16, 18, 19,
		// BOTTOM
		20, 22, 21,
		20, 22, 23
	};

	VertexArray vao;
	vao.Bind();

	Buffer vbo(Buffer::Type::VertexBuffer);
	vbo.Bind();
	vbo.SetData(vertices, sizeof(vertices));

	Buffer ibo(Buffer::Type::IndexBuffer);
	ibo.Bind();
	ibo.SetData(indices, sizeof(indices));

	VertexBufferLayout layout;
	layout.Push<float>(3); // position
	layout.Push<float>(3); // color
	layout.Push<float>(2); // texture
	vao.AddVertexBufferLayout(layout);

	vao.Unbind();

	Shader shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");
	Texture texture("../res/textures/grass.png");


	Camera camera;
	InputManager inputManager(m_window);
	inputManager.RegisterAgent(&camera);

	while (!m_window->ShouldClose()) {
		m_renderer->SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		m_renderer->Clear();

		shader.Bind();
		texture.Bind();
		vao.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();

		shader.SetUniform("model", model);
		shader.SetUniform("view", view);
		shader.SetUniform("projection", projection);
		m_renderer->Draw(sizeof(indices));

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		shader.SetUniform("model", model);
		m_renderer->Draw(sizeof(indices));

		// check and call events and swap the buffers
		m_window->SwapBuffers();

		// Update the input events
		inputManager.Update();

		// Print the FPS
		double currentTime = glfwGetTime();
		static float lastPrintTime = currentTime;
		if (currentTime - lastPrintTime >= 0.5) {
			std::cout << "\rFPS: " << (int)m_window->GetFPS() << "         " << std::flush;
			lastPrintTime = currentTime;
		}
	}
}
