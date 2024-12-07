#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "core/Window.hpp"
#include "core/Renderer.hpp"

#include "graphics/Buffer.hpp"

int main() {
    Window window(800, 600, "VoxelView");
    if (!window.Init()) {
		std::cerr << "Failed to initialize window" << std::endl;
		return -1;
	}

    Renderer renderer;
    if (!renderer.Init()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return -1;
    }

    float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

    unsigned int indices[] = {
		0, 1, 2
	};

    Buffer vbo(Buffer::Type::VertexBuffer);
    vbo.SetData(vertices, sizeof(vertices));

    Buffer ibo(Buffer::Type::IndexBuffer);
    ibo.SetData(indices, sizeof(indices));

    while (!window.ShouldClose()) {
        // rendering commands here
        renderer.SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        renderer.Clear();

        // check and call events and swap the buffers
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}
