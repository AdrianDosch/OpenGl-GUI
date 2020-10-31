#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void)
{
    Window window("Gui test", 800, 600);
    window.setOpenGlVersion(4, 4, GLFW_OPENGL_CORE_PROFILE);

    glfwSetFramebufferSizeCallback(window.windowID, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GUI gui(&window, "example");
    gui.setTitleColor(glm::vec3(0.1f, 0.7f, 0.1f));

    bool Bool1 = false;
    bool Bool2 = true;
    CheckBox box(&gui, &Bool1, "bool 1");
    CheckBox box2(&gui, &Bool2, "bool 2");

    float testFloat = 1.f;
    Slider slider(&gui, &testFloat, 0.f, 2.f, "slider");

    Renderer renderer(&window);
    
    while (!glfwWindowShouldClose(window.windowID)) 
    {
        //std::cout << glGetError() << std::endl;

        /* update uniforms */
        gui.updateInput();
        //std::cout << testFloat << std::endl;

        /* Render here */
        renderer.clear();

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