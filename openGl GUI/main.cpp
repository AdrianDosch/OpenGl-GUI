#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Basic.h"
#include "GUI.h"
#include "Text.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void)
{
    Window window("Gui test", 800, 600);
    window.setOpenGlVersion(4, 4, GLFW_OPENGL_CORE_PROFILE);

    glfwSetFramebufferSizeCallback(window.windowID, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GUI testGUI(&window, "test");
    testGUI.setHight(0.2f);
    testGUI.setWidth(0.3);
    testGUI.setPosition(glm::vec2(0.4f, 0.2f));
    testGUI.setTitle("new title");
    testGUI.setTitleColor(glm::vec3(0.1f, 0.7f, 0.2f));
    testGUI.setColor(glm::vec4(0.1f, 0.3f, 0.4f, 1.f));

    while (!glfwWindowShouldClose(window.windowID)) 
    {
        //std::cout << glGetError() << std::endl;

        /* update uniforms */
       

        /* Render here */
        Renderer::clear();

        testGUI.draw();

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