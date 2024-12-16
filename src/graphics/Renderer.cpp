#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

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

void Renderer::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}