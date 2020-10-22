#include "GUI.h"

GUI::GUI(std::string title /*= ""*/, glm::vec2 position /*= glm::vec2(0.5f, 0.5f)*/, glm::vec4 color /*= glm::vec4(0.1f, 0.4f, 0.3f, 1.f)*/, float width /*= 0.f*/, float hight /*= 0.2*/) :
	m_title(title),
	m_position(position),
	m_color(color),
	m_width(width),
	m_hight(hight),
	m_membercount(0),
	
	m_shader("GUIShader.glsl"),
	m_vboPosition(m_positions, sizeof(m_positions), 0, 2),
	m_vboColor(m_colors, sizeof(m_colors), 1, 4),
	m_ibo(m_indices, sizeof(m_indices))
		
{
	/*std::cout << sizeof(m_positions) << std::endl;
	std::cout << sizeof(m_colors) << std::endl;
	std::cout << sizeof(m_indices) << std::endl;*/
	m_vao.bind();
	m_vboPosition.bind();
	m_vboColor.bind();
	m_ibo.bind();
}

GUI::~GUI()
{

}

void GUI::draw()
{
	m_shader.bind();
	m_shader.setUniformMat4f("u_MVP", m_mvp);
	Renderer::draw(&m_vao, GL_POLYGON, 4);
}

void GUI::setColor(glm::fvec4 color)
{

}

void GUI::setPosition(glm::fvec2 position)
{

}

void GUI::setWidth(float width)
{

}

void GUI::setHight(float hight)
{

}

void GUI::setTitle(std::string title)
{

}

void GUI::setTitleColor(glm::fvec4 color)
{

}
