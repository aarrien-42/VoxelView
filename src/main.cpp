#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Window.hpp"

int main() {
    Window window(800, 600, "VoxelView");

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    while (!window.ShouldClose()) {
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}
