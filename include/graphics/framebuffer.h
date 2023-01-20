#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace unicell
{
	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		unsigned int getTextureID();

		void Bind();
		void Unbind();
	private:
		unsigned int textureID;
		unsigned int id;
	};
}