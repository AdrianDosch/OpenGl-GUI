#include "Rendering.h"

namespace Renderer
{

	inline void draw(VertexArray* vao, GLenum drawMode, int numOfIndices)
	{
		vao->bind();
		glDrawElements(drawMode, numOfIndices, GL_UNSIGNED_INT, nullptr);
	}

	inline void clear(float r, float g, float b, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}
}