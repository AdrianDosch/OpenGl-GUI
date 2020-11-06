#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Includes.h"

#include <iostream>
#include <string>

#include GLM

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GUI.h"

extern class GUI;

class CheckBox
{
private:
	bool* m_variable;
	unsigned int m_position;
	glm::vec3 m_textColor;

	std::string m_text;
	glm::vec4 m_color = glm::vec4(0.8f, 0.6f, 0.1f, 1.f);

	GUI* m_gui;

	VertexArray m_vao;
	VertexBuffer m_vboPosition;
	VertexBuffer m_vboColor;
	IndexBuffer m_ibo;

	float m_positions[8];

	float m_colors[16] =
	{
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a,
		m_color.r, m_color.g, m_color.b, m_color.a
	};

	float m_colors2[16] =
	{
		0.3f, 0.3f, 0.3f, 1.f,
		0.3f, 0.3f, 0.3f, 1.f,
		0.3f, 0.3f, 0.3f, 1.f,
		0.3f, 0.3f, 0.3f, 1.f
	};

	unsigned int m_indices[4] =
	{
		0, 1, 2, 3
	};

public:
	CheckBox(GUI* gui, bool* var, std::string text = "", glm::vec3 textColor = glm::vec3(1.f, 1.f, 1.f));
	~CheckBox();

	void draw();
	void onClick(float xPos, float yPos);
	void setText(std::string text);
};

#endif
