///Opimasation idears:
///-Calculating all the data required to scale and position the title text only if the window is resized or the text is replaced 
///	instead of every frame.
///-only store the vertex and index data on the GPU and have no copy of it for the CPU

#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <variant>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx\string_cast.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Rendering.h"
#include "Text.h"

#include "CheckBox.h"
#include "Slider.h"

namespace GUI
{

	extern class CheckBox;
	extern class Slider;

	class GUI
	{
	private:
		std::string m_titleText;
		glm::fvec3 m_titlecolor;
		glm::fvec4 m_color;
		glm::vec2 m_position;
		float m_width;
		float m_hight;
		bool m_fixPosition = false;

		std::vector<std::variant<CheckBox*, Slider*>> m_members;
		unsigned int m_membercount;
		VertexArray m_vao;
		VertexBuffer m_vboPosition;
		VertexBuffer m_vboColor;
		IndexBuffer m_ibo;

		Text m_title;

		bool m_holdLeftMouse = false;

		float m_positions[8] =
		{
			0.f, 0.f,
			m_width, 0.f,
			m_width, m_hight,
			0.f, m_hight
		};

		float m_colors[16] =
		{
			m_color.r, m_color.g, m_color.b, m_color.a,
			m_color.r, m_color.g, m_color.b, m_color.a,
			m_color.r, m_color.g, m_color.b, m_color.a,
			m_color.r, m_color.g, m_color.b, m_color.a
		};

		unsigned int m_indices[4] =
		{
			0, 1, 2, 3
		};

		void onClick(float xPos, float yPos);

	public:
		GLFWwindow* m_windowID;

		Renderer m_renderer;
		Shader m_shader;

		glm::mat4 m_projection = glm::ortho(0.f, 1.f, 0.f, 1.f);
		glm::mat4 m_model = glm::translate(glm::mat4(1.f), glm::vec3(m_position.x, m_position.y, 0));
		glm::mat4 m_scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f));
		glm::mat4 m_mvp = m_projection * m_model * m_scale;

		GUI(GLFWwindow* windowID, std::string m_title = "", glm::vec2 position = glm::vec2(0.5f, 0.5f), glm::vec4 color = glm::vec4(0.1f, 0.4f, 0.6f, 1.f), float width = 0.5f, float hight = 0.1, std::string pahtToThisHeaderFile = __FILE__);
		~GUI();

		void draw();
		void updateInput();

		void setColor(glm::fvec4 color);
		void setPosition(glm::fvec2 position);
		void setWidth(float width);
		void setHight(float hight);
		void setTitle(std::string title);
		void setTitleColor(glm::fvec3 color);
		void FixPosition(bool state);

		void addComponent(std::variant<CheckBox*, Slider*> component);
		unsigned int getMemerCount();
		glm::vec2 getPosition();
		float getHight();
		float getWidth();

	};

}//end namespace

#endif