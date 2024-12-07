#include "Application.hpp"

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
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
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
	vao.AddVertexBufferLayout(layout);

	vao.Unbind();

	Shader shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");

	while (!m_window->ShouldClose()) {
		m_renderer->SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		m_renderer->Clear();

		shader.Bind();
		vao.Bind();
		m_renderer->Draw();

		// check and call events and swap the buffers
		m_window->SwapBuffers();
		m_window->PollEvents();
	}
}
