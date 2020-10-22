#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include "VertexArray.h"

namespace Renderer
{
	extern inline void draw(VertexArray* vao, GLenum drawMode, int numOfIndices);
	extern inline void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.f);
}

#endif 
