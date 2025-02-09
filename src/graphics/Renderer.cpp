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
	shader.Bind ();

	glm::mat4 model = glm::translate (glm::mat4 (1.0f), mesh.GetPosition ());
	glm::mat4 view = m_camera->GetViewMatrix ();
	glm::mat4 projection = m_camera->GetPerspectiveProjectionMatrix ();

	shader.SetUniform ("model", model);
	shader.SetUniform ("view", view);
	shader.SetUniform ("projection", projection);

	glDrawElements (GL_TRIANGLES, mesh.GetIndexCount (), GL_UNSIGNED_INT, nullptr);
}

// void Renderer::Draw (Text& text, Shader& shader)
// {
// 	shader.Bind ();
// 
// 	glm::mat4 projection = m_camera->GetOrthogonalProjectionMatrix ();
// 
// 	shader.SetUniform ("textColor", text.GetColor ());
// 	shader.SetUniform ("projection", projection);
// 
// 	text.Bind ();
// 	glDrawElements (GL_TRIANGLES, static_cast<GLsizei>(text.GetIndexCount ()), GL_UNSIGNED_INT, nullptr);
// 	text.Unbind ();
// }

void Renderer::SetClearColor (const glm::vec4& color)
{
	glClearColor (color.r, color.g, color.b, color.a);
}