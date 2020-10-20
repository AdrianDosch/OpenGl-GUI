#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    Shader shader("Basic.glsl");
    shader.bind();

    float positions[] = { -0.5f, -0.5f, //0
                       0.5f, -0.5f, //1
                       0.5f,  0.5f, //2
                      -0.5f,  0.5f }; // 3

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vao;
    VertexBuffer vbo(positions, sizeof(positions), 0, 2);
    IndexBuffer ibo(indices, sizeof(indices));

    vao.unbind();
    vbo.unbind();
    ibo.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))          // "Game Loop" one loop "==" one Frame
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.4f, 0.1f, 0.1f, 1.f);

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}