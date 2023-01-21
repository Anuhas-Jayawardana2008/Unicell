#include "graphics/Renderer.h"

namespace unicell
{
	RenderingData Renderer::rendererData;

	void Renderer::DrawQuad(float x,float y,float w,float h,float rotation,const glm::vec4& color)
	{
		glBindVertexArray(rendererData.quadVAO);
		rendererData.quadShader->Bind();
		glEnableVertexAttribArray(0);
		
		const glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(x,y,0.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(w,h,0.0f)) * glm::rotate(glm::mat4(1.0f),glm::radians(rotation),glm::vec3(0.0f,0.0f,1.0f));
		
		rendererData.quadShader->setMat4("projection", Camera::getProjectionMatrix());
		rendererData.quadShader->setMat4("view", Camera::getViewMatrix());
		rendererData.quadShader->setMat4("model", model);
		rendererData.quadShader->setVec4("color", color);

		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0);
		rendererData.quadShader->Unbind();
		glBindVertexArray(0);
	}

	void Renderer::Init()
	{
		const float data[] = {
			-0.5f,-0.5f,0.0f,
			 0.5f,-0.5f,0.0f,
			 0.5f, 0.5f,0.0f,
			-0.5f, 0.5f,0.0f
		};

		glGenVertexArrays(1, &rendererData.quadVAO);
		glBindVertexArray(rendererData.quadVAO);

		rendererData.quadShader = std::make_shared<Shader>("res/basic.glsl");

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

}