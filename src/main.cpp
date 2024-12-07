#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "core/Application.hpp"

int main() {
    Application app = Application(800, 600, "VoxelView");
    if (!app.Init()) {
        return -1;
    }
    app.Run();

    return 0;
}
