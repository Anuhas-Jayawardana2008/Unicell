#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <memory>

#include "graphics/shader.h"
#include "graphics/camera.h"

namespace unicell
{
	struct RenderingData
	{
		unsigned int quadVAO;
		std::shared_ptr<Shader> quadShader;
	};

	class Renderer
	{
	private:
		static RenderingData rendererData;
	public:
		static void Init();
		static void Clear();
		static void DrawQuad(float x,float y,float w,float h,float rotation,const glm::vec4& color);
	};
}