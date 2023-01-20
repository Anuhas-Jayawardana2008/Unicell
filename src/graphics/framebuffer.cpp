#include "graphics/framebuffer.h"

namespace unicell
{
	Framebuffer::Framebuffer()
	{
		int width, height;
		glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glGenFramebuffers(1, &this->id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureID, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &this->id);
	}

	unsigned int Framebuffer::getTextureID()
	{
		return this->textureID;
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}