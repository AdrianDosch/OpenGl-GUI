#include "Window.h"

Window::Window(std::string name, int width /*=0*/, int hight/*=0*/)
	: m_width(width), m_hight(hight)
{
	if (!glfwInit())
		std::cout << "glfw not initialized!" << std::endl;

	windowID = glfwCreateWindow(m_width, m_hight, name.c_str(), NULL, NULL);

	glfwMakeContextCurrent(windowID);

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR: glewInit unsuccessful" << __LINE__ << std::endl;

}

void Window::setOpenGlVersion(int major, int minor, int profile)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void Window::bind()
{
	glfwMakeContextCurrent(windowID);
}

void Window::setSize(unsigned int width, unsigned int hight)
{
	m_hight = hight;
	m_width = width;
}

int Window::getWidth()
{
	return m_width;
}

int Window::getHight()
{
	return m_hight;
}