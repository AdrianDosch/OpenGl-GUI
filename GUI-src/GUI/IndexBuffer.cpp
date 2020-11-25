#include "IndexBuffer.h"
#include <iostream>

namespace GUI
{

IndexBuffer::IndexBuffer(unsigned int indices[], unsigned int size, GLenum drawType)
{
	m_indices = indices;
	m_size = size;
	m_drawType = drawType;

	glGenBuffers(1, &m_IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (void*) indices, drawType);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_IndexBufferID);
}

void IndexBuffer::newData(unsigned int indices[], unsigned int size, GLenum drawType)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (void*)indices, drawType);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, (void*)m_indices, m_drawType);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}// end namespace