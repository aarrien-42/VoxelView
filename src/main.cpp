#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Window.hpp"
#include "core/Renderer.hpp"

int main() {
    Window window(800, 600, "VoxelView");
    Renderer renderer;
    if (!renderer.Init()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return -1;
    }

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
