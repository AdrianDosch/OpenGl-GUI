#pragma once
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>

class VertexBuffer
{
private:
	unsigned int m_VertexBufferID;

public:
	VertexBuffer(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType = GL_STATIC_DRAW, GLenum normalize = GL_FALSE);
	~VertexBuffer();
	void bind();
	void unbind();
};

#endif 