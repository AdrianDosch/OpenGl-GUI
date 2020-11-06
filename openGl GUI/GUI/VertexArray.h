#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Includes.h"

#define GLEW_STATIC
#include GLEW

class VertexArray
{
private:
	unsigned int m_vertexArrayID;

public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
};

#endif