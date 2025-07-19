#include "Renderer.hpp"

Renderer::Renderer ()
	: m_camera (nullptr)
{}

bool Renderer::Init ()
{
	// Initialize GLEW
	if (glewInit () != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	std::cout << "OpenGL Version: " << glGetString (GL_VERSION) << std::endl;

	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetClearColor (glm::vec4 (0.2f, 0.3f, 0.3f, 1.0f));

	return true;
}

void Renderer::Clear ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw (GLsizei count, GLenum mode)
{
	glDrawElements (mode, count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw (Mesh& mesh, Shader& shader)
{
	if (m_camera == nullptr) {
		std::cerr << "Camera is not set" << std::endl;
		return;
	}

	mesh.Bind ();
	shader.Use ();

	glm::mat4 model = glm::translate (glm::mat4 (1.0f), mesh.GetPosition ());
	glm::mat4 view = m_camera->GetViewMatrix ();
	glm::mat4 projection = m_camera->GetPerspectiveProjectionMatrix ();

	shader.SetUniform ("model", model);
	shader.SetUniform ("view", view);
	shader.SetUniform ("projection", projection);

	glDrawElements (GL_TRIANGLES, mesh.GetIndexCount (), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw (Text& text, Shader& shader)
{
	shader.Use ();
	shader.SetUniform ("projection", m_camera->GetOrthogonalProjectionMatrix ());
	shader.SetUniform ("textColor", glm::vec3 (1.0, 0.0, 0.0));

	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;

	// Vertex Array
	vao.Bind ();

	glm::vec2 origin = text.GetPosition ();

	for (const char& c : text.GetText ())
	{
		Character character = text.GetFont ().GetChar (c);
		const float width = character.Size.x;
		const float height = character.Size.y;

		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, character.TextureID);

		glm::vec2 pos = origin;
		pos.y -= character.Bearing.y;
		pos.x += character.Bearing.x;
		float vertices[] = {
			 pos.x + width, pos.y + height, 1.0f, 1.0f, // bottom right
			 pos.x + width, pos.y, 1.0f, 0.0f, // top right
			 pos.x, pos.y, 0.0f, 0.0f, // top left
			 pos.x, pos.y + height, 0.0f, 1.0f  // bottom left
		};
		origin.x += character.Advance >> 6;

		// Vertex Buffer
		vbo.Bind ();
		vbo.SetData (&vertices[0], sizeof (vertices));

		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Index Buffer
		ibo.Bind ();
		ibo.SetData (&indices[0], sizeof (indices));

		// Vertex Buffer Layout
		VertexBufferLayout layout;
		layout.Push<float> (2); // position
		layout.Push<float> (2); // texture
		vao.AddVertexBufferLayout (layout);

		glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	// Unbind
	vao.Unbind ();
}

void Renderer::SetClearColor (const glm::vec4& color)
{
	glClearColor (color.r, color.g, color.b, color.a);
}