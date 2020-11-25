#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#define GLEW_STATIC
#include <GL/glew.h>

namespace GUI
{

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
}//end namespace
#endif