#include "GUI\Includes.h"

#include <iostream>

#include GLEW
#include GLFW3

#include "GUI/GUI.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window window("Gui test", 800, 800);

int main(void)
{
    /**setup OpenGl**/
    window.setOpenGlVersion(4, 4, GLFW_OPENGL_CORE_PROFILE);

    glfwSetFramebufferSizeCallback(window.windowID, framebuffer_size_callback);

    glEnable(GL_BLEND);                                 //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //important!
    glEnable(GL_MULTISAMPLE);


    /**create GUI with its components**/
    GUI gui(&window, "drag me");
    gui.setTitleColor(glm::vec3(0.1f, 0.7f, 0.1f));

    float xPos = 0.f;
    float yPos = 0.f;
    float radius = 0.f;
    Slider slider1(&gui, &xPos, 0.f, 1.f);
    Slider slider2(&gui, &yPos, 0.f, 1.f);
    Slider slider3(&gui, &radius, 0.f, 1.f);

    Renderer renderer(&window);

    glm::mat4 projection = glm::ortho(0.f, 1.f, 0.f, 1.f);
    glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f));
    glm::mat4 mvp = projection * model * scale;
    
    float position[] =
    {
        -1.f, -1.f,
        1.f, -1.f,
        1.f, 1.f,
        -1.f, 1.f
    };

    unsigned int indicesCircle[] =
    {
        0,1,2,3
    };

    Shader circle("Cicle.glsl");
    VertexArray vaoCircle;
    VertexBuffer vboCirclePos(position, sizeof(position), 0, 2);
    IndexBuffer iboCircle(indicesCircle, sizeof(indicesCircle));
    vaoCircle.unbind();
    vboCirclePos.unbind();
    iboCircle.unbind();

    /**program loop**/
    while (!glfwWindowShouldClose(window.windowID)) 
    {
        std::cout << glGetError() << std::endl;
        /* update input */
        gui.updateInput();
        slider1.setText("xPos: " + std::to_string(xPos));
        slider2.setText("yPos: " + std::to_string(yPos));
        slider3.setText("radius: " + std::to_string(radius));

        /* Rendering */
        //example circle
        renderer.clear();

        circle.bind();
        circle.setUniformMat4f("MVP", mvp);
        circle.setUniform2f("radius", radius, 0.f);
        circle.setUniform2f("windowSize", window.getWidth(), window.getHight());
        circle.setUniform2f("ofset", xPos, yPos);
        renderer.draw(&vaoCircle, GL_POLYGON, 4);

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
    ::window.setSize(width, height);
}