#include "Framebuffer.h"

#include <iostream>

Framebuffer::Framebuffer(GLuint width, GLuint height)
{
	_Width = width;
	_Height = height;
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &_Framebuffer);
}

void Framebuffer::GenerateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	GLenum attachmentType;
	if (!depth && !stencil)
		attachmentType = GL_RGB;
	else if (depth && !stencil)
		attachmentType = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachmentType = GL_STENCIL_INDEX;

	glGenTextures(1, &_Texture);
	glBindTexture(GL_TEXTURE_2D, _Texture);

	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachmentType, _Width, _Height, 0, attachmentType, GL_UNSIGNED_BYTE, NULL);
	else // Using both a stencil and depth test
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _Width, _Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _Texture, 0);
}

void Framebuffer::GenerateRenderBuffer()
{
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _Width, _Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void Framebuffer::Create()
{
	glGenFramebuffers(1, &_Framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _Framebuffer);
	GenerateAttachmentTexture(false, false);
	GenerateRenderBuffer();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _Framebuffer);
}
