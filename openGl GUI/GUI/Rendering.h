#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include <string>

#include <glm.hpp>
#include <gtx/string_cast.hpp>

#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"
#include "Text.h"

class Renderer
{
private:
	Window* m_window;
	Shader m_textShader;
	Text m_textObj;

public:
	Renderer(Window* window);
	~Renderer();

	void draw(VertexArray* vao, GLenum drawMode, int numOfIndices);
	void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.f);
	void drawText(std::string text, float xPos, float yPos, float maxHight, float maxWidth, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f));
};


#endif 
