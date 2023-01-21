#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include <string>
#include <iostream>

namespace unicell
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		unsigned int getTextureID();

		void Bind();
		void Unbind();
	private:
		int width, height, bpp;
		unsigned int id;
	};
}