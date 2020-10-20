#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType, GLenum normalize)
{
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

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}