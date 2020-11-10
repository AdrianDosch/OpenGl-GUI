#include "Slider.h"

Slider::Slider(GUI* gui, float* var, float min, float max, std::string text /*= ""*/, glm::vec3 textColor /*= glm::vec3(1.f, 1.f, 1.f)*/, float leftEnd, float rightEnd, float sliderWidth):
	m_variable(var),
	m_min(min),
	m_max(max),
	m_text(text),
	m_textColor(textColor),
	m_leftEnd(leftEnd),
	m_rightEnd(rightEnd),
	m_sliderWidth(sliderWidth),
	m_gui(gui),
	m_vboPositionBar(m_positionsBar, sizeof(m_positionsBar), 0, 2),
	m_vboPositionSlider(m_positionsSlider, sizeof(m_positionsSlider), 0, 2),
	m_vboColorBar(m_colorsBar, sizeof(m_colorsBar), 1, 4),
	m_vboColorSlider(m_colorsSlider, sizeof(m_colorsSlider), 1, 4),
	m_ibo(m_indices, sizeof(m_indices))
{
	gui->addComponent(this);
	m_position = gui->getMemerCount();

	float positionFac = (*m_variable - m_min) / (m_max - m_min);
	float tempPositionsSlider[8]
	{
		(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (1.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (1.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (3.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (3.f / 4.f)
	};
	for (int i = 0; i < 8; i++)
		m_positionsSlider[i] = tempPositionsSlider[i];
	m_vboPositionSlider.newData(m_positionsSlider, sizeof(m_positionsSlider), 0, 2);

	m_vaoSlider.bind();
	m_vboPositionSlider.bind();
	m_vboColorSlider.bind();
	m_ibo.bind();
	m_vaoSlider.unbind();
	m_vboColorSlider.unbind();
	m_vboPositionSlider.unbind();
	m_ibo.unbind();

	float tempPositionsBar[8] =
	{
		m_gui->getWidth() * m_leftEnd, m_gui->getHight() * (6.5f / 15.f),
		m_gui->getWidth() * m_rightEnd, m_gui->getHight() * (6.5f / 15.f),
		m_gui->getWidth() * m_rightEnd, m_gui->getHight() * (8.5f / 15.f),
		m_gui->getWidth() * m_leftEnd, m_gui->getHight() * (8.5f / 15.f),
	};
	for (int i = 0; i < 8; i++)
		m_positionsBar[i] = tempPositionsBar[i];
	m_vboPositionBar.newData(m_positionsBar, sizeof(m_positionsBar), 0, 2);

	m_vaoBar.bind();
	m_vboPositionBar.bind();
	m_vboColorBar.bind();
	m_ibo.bind();
	m_vaoBar.unbind();
	m_vboColorBar.unbind();
	m_vboPositionBar.unbind();
	m_ibo.unbind();
}

Slider::~Slider()
{

}

void Slider::draw()
{
	m_gui->m_renderer.drawText(m_text, m_gui->getPosition().x, m_gui->getPosition().y - m_position * m_gui->getHight(), m_gui->getHight(), m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2)), m_textColor);
	m_gui->m_shader.bind();

	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(m_gui->getPosition().x, m_gui->getPosition().y - (m_gui->getHight() * m_position), 0));
	glm::mat4 mvp = m_gui->m_projection * model;

	m_gui->m_shader.setUniformMat4f("u_MVP", mvp);
	m_gui->m_renderer.draw(&m_vaoBar, GL_POLYGON, 4);
	m_gui->m_renderer.draw(&m_vaoSlider, GL_POLYGON, 4);
	
}

void Slider::onClick(float xPos, float yPos)
{
	m_vaoSlider.bind();

	xPos = xPos / m_gui->m_window->getWidth();
	yPos = yPos / m_gui->m_window->getHight();
	yPos = 1 - yPos;

	if (xPos - m_gui->getPosition().x > 0 && xPos - m_gui->getPosition().x < m_gui->getWidth() && 
		yPos - m_gui->getPosition().y + m_gui->getHight() * m_position > 0 && yPos - m_gui->getPosition().y + m_gui->getHight() * m_position < m_gui->getHight())
	{
		

		glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(m_gui->getPosition().x, m_gui->getPosition().y - (m_gui->getHight() * m_position), 0));
		glm::mat4 mvp = m_gui->m_projection * model;

		glm::vec4 pos = glm::vec4(xPos, yPos, 0.f, 0.f);

		float positionFac = (xPos - m_gui->getPosition().x - m_leftEnd * m_gui->getWidth()) / (m_gui->getWidth() * (m_rightEnd) - m_leftEnd * m_gui->getWidth());

		if (positionFac < 0)
			positionFac = 0.f;
		else if (positionFac > 1)
			positionFac = 1.f;

		*m_variable = (m_max * positionFac) + (m_min * (1 - positionFac));

		float tempPositionsSlider[8]
		{
			(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_rightEnd - m_leftEnd) * positionFac)), m_gui->getHight() * (1.f / 4.f),
			(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_rightEnd - m_leftEnd) * positionFac)), m_gui->getHight() * (1.f / 4.f),
			(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_rightEnd - m_leftEnd) * positionFac)), m_gui->getHight() * (3.f / 4.f),
			(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_rightEnd - m_leftEnd) * positionFac)), m_gui->getHight() * (3.f / 4.f)
		};
		for (int i = 0; i < 8; i++)
			m_positionsSlider[i] = tempPositionsSlider[i];

		m_vboPositionSlider.newData(m_positionsSlider, sizeof(m_positionsSlider), 0, 2);
		m_vaoSlider.unbind();
	}
}

void Slider::setText(std::string text)
{
	m_text = text;
}

void Slider::setTextColor(float r, float g, float b)
{
	m_textColor = glm::vec3(r, g, b);
}

void Slider::setPositionBar(float leftEnd, float rightEnd)
{
	m_leftEnd = leftEnd;
	m_rightEnd = rightEnd;

	float tempPositionsBar[8] =
	{
		m_gui->getWidth() * m_leftEnd, m_gui->getHight() * (6.5f / 15.f),
		m_gui->getWidth() * m_rightEnd, m_gui->getHight() * (6.5f / 15.f),
		m_gui->getWidth() * m_rightEnd, m_gui->getHight() * (8.5f / 15.f),
		m_gui->getWidth() * m_leftEnd, m_gui->getHight() * (8.5f / 15.f),
	};
	for (int i = 0; i < 8; i++)
		m_positionsBar[i] = tempPositionsBar[i];
	m_vaoBar.bind();
	m_vboPositionBar.newData(m_positionsBar, sizeof(m_positionsBar), 0, 2);
	m_vaoBar.unbind();
}

void Slider::setWidthSlider(float width)
{
	m_sliderWidth = width;

	float positionFac = (*m_variable - m_min) / (m_max - m_min);
	float tempPositionsSlider[8]
	{
		(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (1.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (1.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd + (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (3.f / 4.f),
		(m_gui->getWidth() * (m_leftEnd - (m_sliderWidth / 2) + (m_leftEnd - m_sliderWidth) * positionFac)), m_gui->getHight() * (3.f / 4.f)
	};
	for (int i = 0; i < 8; i++)
		m_positionsSlider[i] = tempPositionsSlider[i];
	m_vaoSlider.bind();
	m_vboPositionSlider.newData(m_positionsSlider, sizeof(m_positionsSlider), 0, 2);
	m_vaoSlider.unbind();
}

void Slider::setColorBar(float r, float g, float b, float a)
{
	m_colorBar = glm::vec4(r, g, b, a);

	float tempColor[16] =
	{
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a,
		m_colorBar.r, m_colorBar.g, m_colorBar.b, m_colorBar.a
	};
	for (int i = 0; i < 16; i++)
		m_colorsBar[i] = tempColor[i];
	m_vaoBar.bind();
	m_vboColorBar.newData(m_colorsBar, sizeof(m_colorsBar), 1, 4);
	m_vaoBar.unbind();
}

void Slider::setColorSlider(float r, float g, float b, float a)
{
	m_colorSlider = glm::vec4(r, g, b, a);

	float tempColor[16] =
	{
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a,
		m_colorSlider.r, m_colorSlider.g, m_colorSlider.b, m_colorSlider.a
	};
	for (int i = 0; i < 16; i++)
		m_colorsSlider[i] = tempColor[i];

	m_vaoSlider.bind();
	m_vboColorSlider.newData(m_colorsSlider, sizeof(m_colorsSlider), 1, 4);
	m_vaoSlider.unbind();
}
