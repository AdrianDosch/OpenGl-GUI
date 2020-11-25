#include "VertexBuffer.h"
#include <iostream>

namespace GUI
{

VertexBuffer::VertexBuffer(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType, GLenum normalize)
{
	m_vertices = vertices;
	m_size = size;
	m_drawType = drawType;

	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, (void*) vertices, drawType);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, numOfDatapoints, GL_FLOAT, normalize, sizeof(float) * numOfDatapoints, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexBufferID);
}

void VertexBuffer::newData(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType, GLenum normalize)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, (void*)vertices, drawType);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, numOfDatapoints, GL_FLOAT, normalize, sizeof(float) * numOfDatapoints, 0);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_size, (void*)m_vertices, m_drawType);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}// end namespace