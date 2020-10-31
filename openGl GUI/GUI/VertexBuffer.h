#pragma once
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>

class VertexBuffer
{
private:
	unsigned int m_VertexBufferID;

	float* m_vertices;
	unsigned int m_size;
	GLenum m_drawType;

public:
	VertexBuffer(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType = GL_STATIC_DRAW, GLenum normalize = GL_FALSE);
	VertexBuffer(){}
	~VertexBuffer();
	void newData(float vertices[], unsigned int size, int location, int numOfDatapoints, GLenum drawType = GL_STATIC_DRAW, GLenum normalize = GL_FALSE);
	void bind();
	void unbind();
};

#endif 