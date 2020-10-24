#include "GUI.h"

GUI::GUI(Window* window, std::string title /*= ""*/, glm::vec2 position /*= glm::vec2(0.5f, 0.5f)*/, glm::vec4 color /*= glm::vec4(0.1f, 0.4f, 0.3f, 1.f)*/, float width /*= 0.f*/, float hight /*= 0.2*/) :
	m_titleText(title),
	m_position(position),
	m_color(color),
	m_width(width),
	m_hight(hight),
	m_membercount(0),
	m_window(window),

	m_textShader("TextShader.glsl"),
	m_title(window),

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
	m_mvp = m_projection * m_model * m_scale;
	m_shader.setUniformMat4f("u_MVP", m_mvp);
	Renderer::draw(&m_vao, GL_POLYGON, 4);

	/**render Title**/
	m_textShader.bind();
	glm::mat4 projection = glm::ortho(0.0f, 1.f, 0.0f, 1.f);

	float width = (1 / (float)m_window->getWidth()) * ((float)m_title.getAdvancment(m_titleText) / 64.f);	//
	float hight = (1 / (float)m_window->getHight()) * m_title.getMaxHight(m_titleText);						//size of the Text in percent
	float toMiddle = m_hight / 2 - hight / 2;																// offset to bottom of the Background so the text is in the middle
	glm::mat4 scale = m_scale;

	float resizeFacLenght = 0;																				//
	float resizeFacHight = 0;																				//
	if (width > m_width)																					//
		resizeFacLenght = width * (1.f / m_width);															//
																											//
	if (hight > m_hight)																					//
		resizeFacHight = hight * (1.f / m_hight);															//
																											//
																											//
	if(resizeFacLenght > resizeFacHight)																	//
		scale = glm::scale(glm::mat4(1.f), glm::vec3(1 / resizeFacLenght, 1.f / resizeFacLenght, 1.f));		//
	else if (resizeFacLenght < resizeFacHight)																//
	{																										//
		scale = glm::scale(glm::mat4(1.f), glm::vec3(1 / resizeFacHight, 1.f / resizeFacHight, 1.f));		//
		toMiddle = 0;																						//
	}																										//scaling of the title if it is larger than the background

	m_mvp = m_projection * m_model * scale;
	m_textShader.setUniformMat4f("u_MVP", m_mvp);
	m_title.RenderText(m_textShader, m_titleText, 0.f, toMiddle, 1.f / m_window->getWidth(), 1.f / m_window->getHight(), m_titlecolor);
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
