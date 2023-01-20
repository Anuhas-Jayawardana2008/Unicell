#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <memory>

#include "graphics/shader.h"

namespace unicell
{
	class Renderer
	{
	public:
		static void Clear();
		static void DrawQuad(float x,float y,float w,float h);
	};
}