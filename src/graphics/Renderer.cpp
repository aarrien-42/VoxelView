#include "Renderer.hpp"

Renderer::Renderer()
	: m_camera(nullptr)
{}

bool Renderer::Init()
{
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    
    return true;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(GLsizei count, GLenum mode)
{
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(Mesh& mesh, Shader& shader) {
    if (m_camera == nullptr) {
		std::cerr << "Camera is not set" << std::endl;
		return;
	}

    mesh.Bind();
    shader.Bind();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = m_camera->GetProjectionMatrix();

    shader.SetUniform("model", model);
    shader.SetUniform("view", view);
    shader.SetUniform("projection", projection);

    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}