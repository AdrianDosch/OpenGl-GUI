#include "CheckBox.h"

CheckBox::CheckBox(GUI* gui, bool* var, std::string text, glm::vec3 textColor) :
	m_variable(var),

	m_text(text),
	m_textColor(textColor),
	m_gui(gui),

	m_vboPosition(m_positions, sizeof(m_positions), 0, 2),
	m_vboColor(m_colors, sizeof(m_colors), 1, 4),
	m_ibo(m_indices, sizeof(m_indices))
{
	gui->addComponent(this);
	m_position = gui->getMemerCount();

	float positions[8] =
	{
		m_gui->getWidth() * (17.f / 20.f), m_gui->getHight() * (1.f / 4.f),
		m_gui->getWidth() * (19.f / 20.f), m_gui->getHight()* (1.f / 4.f),
		m_gui->getWidth() * (19.f / 20.f), m_gui->getHight()* (3.f / 4.f),
		m_gui->getWidth() * (17.f / 20.f), m_gui->getHight()* (3.f / 4.f),
	};

	for (int i = 0; i < 8; i++)
		m_positions[i] = positions[i];
	m_vboPosition.newData(m_positions, sizeof(m_positions), 0, 2);

	m_vao.bind();
	m_vboPosition.bind();
	m_vboColor.bind();
	m_ibo.bind();
	m_vao.unbind();
	m_vboColor.unbind();
	m_vboPosition.unbind();
	m_ibo.unbind();

	m_vao.bind();
	if (*m_variable)
		m_vboColor.newData(m_colors2, sizeof(m_colors2), 1, 4);
	m_vao.unbind();
}

CheckBox::~CheckBox()
{

}

void CheckBox::draw()
{
	m_gui->m_renderer.drawText(m_text, m_gui->getPosition().x, m_gui->getPosition().y - m_position * m_gui->getHight(), m_gui->getHight(), m_gui->getWidth() * (17.f / 20.f), m_textColor);
	m_gui->m_shader.bind();

	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(m_gui->getPosition().x, m_gui->getPosition().y - (m_gui->getHight() * m_position), 0));
	glm::mat4 mvp1 = m_gui->m_projection * model;

	m_gui->m_shader.setUniformMat4f("u_MVP", mvp1);
	m_gui->m_renderer.draw(&m_vao, GL_POLYGON, 4);
}

void CheckBox::onClick(float xPos, float yPos)
{
	xPos = xPos / m_gui->m_window->getWidth();
	yPos = yPos / m_gui->m_window->getHight();
	yPos = 1 - yPos;

	if (xPos - m_gui->getPosition().x > 0 && xPos - m_gui->getPosition().x < m_gui->getWidth() &&
		yPos - m_gui->getPosition().y + m_gui->getHight() * m_position > 0 && yPos - m_gui->getPosition().y + m_gui->getHight() * m_position < m_gui->getHight())
	{
		*m_variable = !*m_variable;
		m_vao.bind();
		if (*m_variable)
			m_vboColor.newData(m_colors2, sizeof(m_colors2), 1, 4);
		else
			m_vboColor.newData(m_colors, sizeof(m_colors), 1, 4);
		m_vao.unbind();
	}
}

void CheckBox::setText(std::string text)
{
	m_text = text;
}