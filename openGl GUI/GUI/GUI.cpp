#include "GUI.h"

GUI::GUI(GLFWwindow* windowID, std::string title /*= ""*/, glm::vec2 position /*= glm::vec2(0.5f, 0.5f)*/, glm::vec4 color /*= glm::vec4(0.1f, 0.4f, 0.3f, 1.f)*/, float width /*= 0.f*/, float hight /*= 0.2*/) :
	m_titleText(title),
	m_position(position),
	m_color(color),
	m_width(width),
	m_hight(hight),
	m_membercount(0),
	m_windowID(windowID),

	m_title(windowID),
	m_renderer(windowID),

	m_shader("GUI/Shaders/GUIShader.glsl"),
	m_vboPosition(m_positions, sizeof(m_positions), 0, 2),
	m_vboColor(m_colors, sizeof(m_colors), 1, 4),
	m_ibo(m_indices, sizeof(m_indices))
		
{
	m_vao.bind();
	m_vboPosition.bind();
	m_vboColor.bind();
	m_ibo.bind();
	m_vao.unbind();
	m_vboColor.unbind();
	m_vboPosition.unbind();
	m_ibo.unbind();
}

GUI::~GUI()
{

}

void GUI::draw()
{
	/**render background**/
	m_shader.bind();
	m_mvp = m_projection * m_model * glm::translate(glm::mat4(1.f), glm::vec3(0, -m_hight * m_membercount, 0)) * glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f + m_membercount, 1.f));
	m_shader.setUniformMat4f("u_MVP", m_mvp);
	m_renderer.draw(&m_vao, GL_POLYGON, 4);

	/**render Title**/
	m_renderer.drawText(m_titleText, m_position.x, m_position.y, m_hight, m_width, m_titlecolor);
	
	/**render components**/
	for (int i = 0; i < m_members.size(); i++)					
	{															
		if(m_members.at(i).index() == 0)						
			std::get<CheckBox*>(m_members.at(i))->draw();		
		else if (m_members.at(i).index() == 1)					
			std::get<Slider*>(m_members.at(i))->draw();			
	}

}

void GUI::updateInput()
{
	if (glfwGetMouseButton(m_windowID, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xPos, yPos = 0;
		glfwGetCursorPos(m_windowID, &xPos, &yPos);

		for (int i = 0; i < m_members.size(); i++)
		{
			if (m_members.at(i).index() == 0 && m_holdLeftMouse == false)
				std::get<CheckBox*>(m_members.at(i))->onClick(xPos, yPos);
			else if (m_members.at(i).index() == 1)
				std::get<Slider*>(m_members.at(i))->onClick(xPos, yPos);
		}
		if(!m_fixPosition)
			onClick(xPos, yPos);
		m_holdLeftMouse = true;
	}
	else
		m_holdLeftMouse = false;
}

void GUI::onClick(float xPos, float yPos)
{
	int screenWidth, screenHeight;
	glfwGetWindowSize(m_windowID, &screenWidth, &screenHeight);

	xPos = xPos / screenWidth;
	yPos = yPos / screenHeight;
	yPos = 1 - yPos;

	if (xPos - getPosition().x > 0 && xPos - getPosition().x < getWidth() &&
		yPos - getPosition().y  > 0 && yPos - getPosition().y < getHight())
	{
		setPosition(glm::vec2(xPos - getWidth() / 2, yPos -getHight() / 2));
	}
}

void GUI::setColor(glm::fvec4 color)
{
	float tempColors[16] =
	{
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a
	};

	for (int i = 0; i < 16; i++)
		m_colors[i] = tempColors[i];
	m_vboColor.newData(m_colors, sizeof(m_colors), 1, 4);
}

void GUI::setPosition(glm::fvec2 position)
{
	m_position = position;
	m_model = glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
}

void GUI::setWidth(float width)
{
	float tempPositions[8] =
	{
		0.f, 0.f,
		width, 0.f,
		width, m_hight,
		0.f, m_hight
	};
	
	for (int i = 0; i < 8; i++)
		m_positions[i] = tempPositions[i];
	m_vboPosition.newData(m_positions, sizeof(m_positions), 0, 2);
	m_width = width;
}

void GUI::setHight(float hight)
{
	float tempPositions[8] =
	{
		0.f, 0.f,
		m_width, 0.f,
		m_width, hight,
		0.f, hight
	};

	for (int i = 0; i < 8; i++)
		m_positions[i] = tempPositions[i];
	m_vboPosition.newData(m_positions, sizeof(m_positions), 0, 2);
	m_hight = hight;
}

void GUI::setTitle(std::string title)
{
	m_titleText = title;
}

void GUI::setTitleColor(glm::fvec3 color)
{
	m_titlecolor = color;
}

void GUI::addComponent(std::variant<CheckBox*, Slider*> component)
{
	m_membercount++;
	m_members.push_back(component);
}

void GUI::FixPosition(bool state)
{
	m_fixPosition = state;
}

unsigned int GUI::getMemerCount()
{
	return m_membercount;
}

glm::vec2 GUI::getPosition()
{
	return m_position;
}

float GUI::getHight()
{
	return m_hight;
}

float GUI::getWidth()
{
	return m_width;
}
