// openGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef long long ll;
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.9f, 0.09f, 1.0f);\n"
"}\n\0";

int main()
{
    // init function
    glfwInit();

    // config inits
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // triangle object
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
        0.0f, 1.0f * float(sqrt(3)) / 3, 0.0f
    };

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

    // create shader and pre compile shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // attach shader to program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // store shape in buffer
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // main while loop
    while (!glfwWindowShouldClose(window)) {
        // clear for every frame
        glClearColor(0.18f, 0.18f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // run shader
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // swap the buffers on each run
        glfwSwapBuffers(window);

        // runner
        glfwPollEvents();
    }

    /* clean up */
    // gl objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    // window instance
    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout << "Done\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
