#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include <string>

#include <glm.hpp>
#include <gtx/string_cast.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GUI.h"

extern class GUI;

class Slider
{
private:
	float* m_variable;
	float m_min;
	float m_max;
	unsigned int m_position;
	glm::vec3 m_textColor;

	std::string m_text;
	glm::vec4 m_color = glm::vec4(0.8f, 0.6f, 0.1f, 1.f);

	GUI* m_gui;

	VertexArray m_vaoBar;
	VertexBuffer m_vboPositionBar;
	VertexBuffer m_vboColorBar;
	IndexBuffer m_ibo;

	VertexArray m_vaoSlider;
	VertexBuffer m_vboPositionSlider;
	VertexBuffer m_vboColorSlider;

	float m_positionsBar[8];
	float m_positionsSlider[8];

	unsigned int m_indices[4] =
	{
		0, 1, 2, 3
	};

	float m_colorsBar[16] =
	{
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a
	};

	float m_colorsSlider[16] =
	{
		0.9f, m_color.g, m_color.b, m_color.a,
		0.9f, m_color.g, m_color.b, m_color.a,
		0.9f, m_color.g, m_color.b, m_color.a,
		0.9f, m_color.g, m_color.b, m_color.a
	};

public:
	Slider(GUI* gui, float* var, float min, float max, std::string text = "", glm::vec3 textColor = glm::vec3(1.f, 1.f, 1.f));
	~Slider();

	void draw();
	void onClick(float xPos, float yPos);
	void setText(std::string text);
};


#endif