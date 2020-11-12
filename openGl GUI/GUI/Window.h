#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <gl/glew.h>
#endif

#include <GLFW/glfw3.h>

class Window
{
private:
	int m_hight;
	int m_width;

public:
	GLFWwindow* windowID;

	Window(std::string name, int width = 600, int hight = 600);

	void setOpenGlVersion(int major, int minor, int profile);

	void bind();
	void setSize(unsigned int width, unsigned int hight);
	int getWidth();
	int getHight();
};

#endif