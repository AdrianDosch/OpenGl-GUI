#include "Rendering.h"

Renderer::Renderer(GLFWwindow* m_windowID):
	m_windowID(m_windowID),
	m_textShader("GUI/Shaders/TextShader.glsl"),
	m_textObj(m_windowID)
{

}

Renderer::~Renderer()
{

}

void Renderer::draw(VertexArray* vao, GLenum drawMode, int numOfIndices)
{
	vao->bind();
	glDrawElements(drawMode, numOfIndices, GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear(float r, float g, float b, float a)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void Renderer::drawText(std::string text, float xPos, float yPos, float maxHight, float maxWidth, glm::vec3 color)
{
	m_textShader.bind();

	int screenWidth, screenHeight;
	glfwGetWindowSize(m_windowID, &screenWidth, &screenHeight);

	float width = (1 / (float)screenWidth) * ((float)m_textObj.getAdvancment(text) / 64.f);		//
	float hight = (1 / (float)screenWidth) * m_textObj.getMaxHight(text);							// size of the Text in percent
	float toMiddle = maxHight / 2 - hight / 2;																// offset to bottom of the Background so the text is in the middle

	glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f));									//
	float resizeFacLenght = 0;																				//
	float resizeFacHight = 0;																				//
	if (width > maxWidth)																					//
		resizeFacLenght = width * (1.f / maxWidth);															//
																											//
	if (hight > maxHight)																					//
		resizeFacHight = hight * (1.f / maxHight);															//
																											//
																											//
	if(resizeFacLenght > resizeFacHight)																	//
		scale = glm::scale(glm::mat4(1.f), glm::vec3(1 / resizeFacLenght, 1.f / resizeFacLenght, 1.f));		//
	else if (resizeFacLenght < resizeFacHight)																//
	{																										//
		scale = glm::scale(glm::mat4(1.f), glm::vec3(1 / resizeFacHight, 1.f / resizeFacHight, 1.f));		//
		toMiddle = 0;																						//
	}																										//scaling of the title if it is larger than the background

	glm::mat4 projection = glm::ortho(0.f, 1.f, 0.f, 1.f);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(xPos, yPos, 0));
	glm::mat4 mvp = projection * model * scale;
	m_textShader.setUniformMat4f("u_MVP", mvp);
	m_textObj.RenderText(m_textShader, text, 0.f, toMiddle, 1.f / screenWidth, 1.f / screenHeight, color);
}