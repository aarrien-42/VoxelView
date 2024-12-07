#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "core/Window.hpp"
#include "core/Renderer.hpp"

#include "graphics/Buffer.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/Shader.hpp"

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

    while (!window.ShouldClose()) {
        // rendering commands here
        renderer.SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        renderer.Clear();

        shader.Bind();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        // check and call events and swap the buffers
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}
