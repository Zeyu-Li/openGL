// openGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef long long ll;

int main()
{
    // init function
    glfwInit();

    // config inits
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window height and width set to the same at 800px
    int height, width;
    height = width = 800;
    const char* windowName = "OpenGL - Test";
    bool fullscreen = false;

    // window object
    GLFWwindow* window = glfwCreateWindow(height, width, windowName, NULL, NULL);

    // if window could not be initalized
    if (!window) {
        std::cout << "Could not load window :(\n";
        glfwTerminate();
        return -1;
    }

    // create window instance
    glfwMakeContextCurrent(window);

    // main while loop
    while (!glfwWindowShouldClose(window)) {
        // runner
        glfwPollEvents();
    }

    // clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout << "Done\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
