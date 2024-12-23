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
	 // position         // normal

	// FRONT
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 0
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 1
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 2
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 3

	// BACK				 
 	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 4
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 5
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 6
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 7

	// LEFT				 				 
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // 8
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // 9
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // 10
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // 11

	// RIGTH			 				 
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // 12
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // 13
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // 14
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // 15

	 // TOP				 				 
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // 16
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // 17
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // 18
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // 19

	// BOTTOM			 				 
 	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // 20
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // 21
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // 22
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // 23
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

	std::vector<Vertex> meshVertices {
		// FRONT
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2( 0.0f,  0.0f)},  // 0 => Bottom Left
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2( 1.0f,  0.0f)},  // 1 => Bottom Right
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2( 1.0f,  1.0f)},  // 2 => Top Right
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2( 0.0f,  1.0f)},  // 3 => Top Left
																		
		// BACK															
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2( 0.0f,  0.0f)},  // 4
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2( 1.0f,  0.0f)},  // 5 
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2( 1.0f,  1.0f)},  // 6
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2( 0.0f,  1.0f)},  // 7
																		
		// LEFT				 				 							
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  0.0f)},  // 8
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  0.0f)},  // 9
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  1.0f)},  // 10
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  1.0f)},  // 11
																		
		// RIGTH														
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  0.0f)},  // 12
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  0.0f)},  // 13
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  1.0f)},  // 14
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  1.0f)},  // 15
																		
		// TOP				 				 							
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 0.0f,  0.0f)},  // 16
		{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 1.0f,  0.0f)},  // 17
		{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 1.0f,  1.0f)},  // 18
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 0.0f,  1.0f)},  // 19
																		
		// BOTTOM			 				 							
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 0.0f,  0.0f)},  // 20
		{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 1.0f,  0.0f)},  // 21
		{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 1.0f,  1.0f)},  // 22
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 0.0f,  1.0f)}   // 23
	};

	std::vector<unsigned int> meshIndices{
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

	Texture meshTexture("../res/textures/grass.png");

	Mesh mesh(meshVertices, meshIndices, meshTexture);

	Shader shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");

	Camera camera;
	InputManager inputManager(m_window);
	inputManager.RegisterAgent(&camera);
	m_renderer->SetCamera(camera);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	while (!m_window->ShouldClose()) {
		m_renderer->SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		m_renderer->Clear();

		// Draw mesh
		m_renderer->Draw(mesh, shader);

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
