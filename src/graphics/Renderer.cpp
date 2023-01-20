#include "graphics/Renderer.h"

namespace unicell
{

	void Renderer::DrawQuad(float x,float y,float w,float h)
	{
	}

	void Renderer::Clear()
	{
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}