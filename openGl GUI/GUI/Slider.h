#ifndef SLIDER_H
#define SLIDER_H

#include "Includes.h"

#include <iostream>
#include <string>

#include GLM
#include STRING_CAST

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
	glm::vec4 m_colorBar = glm::vec4(0.8f, 0.6f, 0.1f, 1.f);
	glm::vec4 m_colorSlider = glm::vec4(0.9f, 0.6f, 0.1f, 1.f);

	float m_leftEnd = 0.5f;
	float m_rightEnd = (19.f / 20.f);
	float m_sliderWidth = (1.f/20.f);

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
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a
	};

	float m_colorsSlider[16] =
	{
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a
	};

public:
	Slider(GUI* gui, float* var, float min, float max, std::string text = "", glm::vec3 textColor = glm::vec3(1.f, 1.f, 1.f), float leftEnd = 0.5f, float rightEnd = (19.f/20.f), float sliderWidth = (1.f/20.f));
	~Slider();

	void draw();
	void onClick(float xPos, float yPos);
	void setText(std::string text);
	void setTextColor(float r = 1.f, float g = 1.f, float b = 1.f);
	void setPositionBar(float leftEnd = 0.5f, float rightEnd = (19.f/20.f));
	void setWidthSlider(float width = (1.f/20.f));
	void setColorBar(float r = 0.8f, float g = 0.6f, float b = 0.1f, float a = 1.f);
	void setColorSlider(float r = 0.9f, float g = 0.6f, float b = 0.1f, float a = 1.f);
};


#endif