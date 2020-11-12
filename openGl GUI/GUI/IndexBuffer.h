#pragma once
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#define GLEW_STATIC
#include <gl/glew.h>

class IndexBuffer
{
private:
	unsigned int m_IndexBufferID;

	unsigned int* m_indices;
	unsigned int m_size;
	GLenum m_drawType;

public:
	IndexBuffer(unsigned int indices[], unsigned int size, GLenum drawType = GL_STATIC_DRAW);
	IndexBuffer(){}
	~IndexBuffer();
	void newData(unsigned int indices[], unsigned int size, GLenum drawType = GL_STATIC_DRAW);
	void bind();
	void unbind();
};

#endif