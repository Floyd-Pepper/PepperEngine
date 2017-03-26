#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineManager.h"

#include <string>

class Framebuffer
{
public:
	Framebuffer(GLuint width = 1920, GLuint height = 1080);
	~Framebuffer();
	void Create();
	void Activate();

	GLuint GetTextureID() const { return _Texture; }

private:
	void GenerateAttachmentTexture(GLboolean depth, GLboolean stencil);
	void GenerateRenderBuffer();

private:
	GLuint _Width;
	GLuint _Height;
	GLuint _Framebuffer;
	GLuint _Texture;

	int a = 10;
	int b = 5;
};