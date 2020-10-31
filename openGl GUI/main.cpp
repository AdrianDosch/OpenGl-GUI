#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void)
{
    /**init openGl and create window**/
    Window window("Gui test", 800, 600);
    window.setOpenGlVersion(4, 4, GLFW_OPENGL_CORE_PROFILE);

    glfwSetFramebufferSizeCallback(window.windowID, framebuffer_size_callback);

    glEnable(GL_BLEND);                                 //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //important!


    /**create GUI with its components**/
    GUI gui(&window, "drag me");
    gui.setTitleColor(glm::vec3(0.1f, 0.7f, 0.1f));

    bool showSquare = true;
    CheckBox checkBox1(&gui, &showSquare, "show sqare?:");

    float xPos = 0.f;
    float yPos = 0.f;
    Slider slider1(&gui, &xPos, 0.f, 1.f, "xPos:");
    Slider slider2(&gui, &yPos, 0.f, 1.f, "yPos:");

    /**creation of the example square**/
    Renderer renderer(&window);
    float positions[] =
    {
        //pos         //texCoord
        0.f, 0.f,  
        0.25f, 0.f, 
        0.25f, 0.25f,
        0.f, 0.25f
    };

    unsigned int indices[]
    {
        0, 1, 2, 3
    };

    Shader shader("Basic.glsl");
    VertexArray vao;
    VertexBuffer vbo(positions, sizeof(positions), 0, 2);
    IndexBuffer ibo(indices, sizeof(indices));
    vao.unbind();
    vbo.unbind();
    ibo.unbind();

    glm::mat4 projection = glm::ortho(0.f, 1.f, 0.f, 1.f);
    glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f));
    glm::mat4 mvp = projection * model * scale;
    
    while (!glfwWindowShouldClose(window.windowID)) 
    {
        /* update input */
        gui.updateInput();

        /* Rendering */
        //example sqare
        renderer.clear();
        if (showSquare)
        {
            shader.bind();
            model = glm::translate(glm::mat4(1.f), glm::vec3(xPos, yPos, 0.f));
            mvp = projection * model * scale;
            shader.setUniformMat4f("MVP", mvp);
            renderer.draw(&vao, GL_POLYGON, 4);
        }

        //draw gui with components --> neads to be drawn last 
        gui.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.windowID);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}