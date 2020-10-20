#pragma once
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>

class IndexBuffer
{
private:
	unsigned int m_IndexBufferID;

public:
	IndexBuffer(unsigned int indices[], unsigned int size, GLenum drawType = GL_STATIC_DRAW);
	~IndexBuffer();
	void bind();
	void unbind();
};

#endif