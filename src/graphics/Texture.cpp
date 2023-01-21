#include "graphics/Texture.h"

namespace unicell
{
	Texture::Texture(const std::string& path)
	{
		unsigned char* pixels = stbi_load(path.c_str(), &this->width, &this->height, &this->bpp, 4);

		if (pixels == NULL)
		{
			std::cout << "[Texture Error] : Failed to load " << path << std::endl;
		}

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		stbi_image_free(pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	unsigned int Texture::getTextureID()
	{
		return this->id;
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, this->id);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}