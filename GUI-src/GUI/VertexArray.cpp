#include "VertexArray.h"

namespace GUI
{

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
}// end namespace