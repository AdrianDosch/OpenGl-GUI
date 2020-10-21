#include "VertexArray.h"
namespace Renderer
{

	inline void draw(VertexArray* vao, GLenum drawMode, int numOfIndices)
	{
		vao->bind();
		glDrawElements(drawMode, numOfIndices, GL_UNSIGNED_INT, nullptr);
	}

	inline void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.f)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

}