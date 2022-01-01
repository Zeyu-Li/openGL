// openGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

typedef long long ll;
// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.9f, 0.9f, 0.09f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.5f, 0.9f, 0.09f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.5f, 0.9f, 0.09f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.9f, 0.09f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.9f, 0.09f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.9f, 0.5f, 0.09f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

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

    // update window screen to black
    gladLoadGL();

    // render view has a shown and buffer loading in the background
    // we want to swap the buffer such that the buffer content gets displayed
    glViewport(0, 0, height, width);

    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // main while loop
    while (!glfwWindowShouldClose(window)) {
        // clear for every frame
        glClearColor(0.18f, 0.18f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // run shader
        shaderProgram.Activate();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        // swap the buffers on each run
        glfwSwapBuffers(window);

        // runner
        glfwPollEvents();
    }

    /* clean up */
    // gl objects
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    // window instance
    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout << "Done\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
